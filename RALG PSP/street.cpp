object car[25];
object player;
object police;//chance 800-score/30 if no police create one at 0,player.y verify if is something there, if not continue, speed = 1.5, move to the player.y coord with 2 units, animation speed 1 donno
object gas;
OSL_SOUND *music,*crash,*siren;

void create_car( int type){
		for(int i=0;i<=20;i++)
			if(car[i].On==0){
				car[i].On=1;
				car[i].type=type;																								//1=left 2=right
				car[i].frame=rand()%4+1;																					//car color
				if(car[i].image!=0)
					oslDeleteImage(car[i].image);
				car[i].image=oslCreateImageCopy(graphics[9+car[i].frame],OSL_IN_RAM);	//load the image
				oslSetImageTileSize(car[i].image,(car[i].type-1)*64,0,64,32);						//resize it
				if(car[i].type==1){																								//if left or right
					car[i].image->x=560;																						//x coordonate
					car[i].image->y=89;																						//y coordonate
					car[i].mx=-6;																								//speed
					if(rand()%2==1){																							//change the band
						car[i].image->y=48;																					//y coordonate
						car[i].mx=-5;
						if(rand()%2==1){
							car[i].image->y=10;																				//y coordonate
							car[i].mx=-4;
						}
					}
				}else	if(car[i].type==2){
						car[i].image->x=560;																					//x coordonate
						car[i].image->y=224;																					//y coordonate
						car[i].mx=-3;
						if(rand()%2==1){
							car[i].image->y=183;																				//y coordonate
							car[i].mx=-2;
							if(rand()%2==1){
								car[i].image->y=136;																			//y coordonate
								car[i].mx=-1;
							}
						}
				}
				for(int j=0;j<=20;j++)
					if(car[j].On==1 && j!=i && car[j].image!=0 && collision(car[i].image,car[j].image) && (car[i].image->x>car[j].image->x-80 && car[i].type==2 || car[i].image->x<car[j].image->x+80 && car[i].type==1)){
						//oslDeleteImage(car[i].image);
						car[i].On=0;
						break;
					}
				break;
			}
}

int street_main ()
{
	player.image=oslCreateImageCopy(graphics[20],OSL_IN_RAM);
	gas.image = oslCreateImageCopy(graphics[21],OSL_IN_RAM);
	police.image = oslCreateImageCopy(graphics[22],OSL_IN_RAM);
	crash = oslLoadSoundFileWAV("sounds/collision.wav",OSL_FMT_NONE);
	siren = oslLoadSoundFileWAV("sounds/siren.wav",OSL_FMT_NONE);
	player.image->centerX=32;
	player.image->centerY=16;
	int score=0, pause=0,check=0, vlr=0,vud=0;
	frame=0;
	done=0;
	while(osl_quit!=1){
		oslSetFont(big_font);
		oslSetTextColor(white);
		oslReadKeys();
		oslStartDrawing();
		if(pause==0){
			oslDrawImageXY(title[12],frame,0);
			oslDrawImageXY(title[12],frame+480,0);
			for(int i=0;i<=20;i++){
				if(car[i].On==1){
					//fprintf(debugh,"Id:%4d X:%4d Y:%4d Ty:%4d Fr:%4d Mx:%4.0lf Img: %d\n",i,car[i].image->x,car[i].image->y,car[i].type,car[i].frame,car[i].mx,car[i].image && 1);
					oslDrawImage(car[i].image);
					car[i].update();
					if(car[i].is_off_screen() && car[i].image->x<0 ){
						car[i].On=0;
						continue;
					}
					if(collision(player.image,car[i].image)==1 && player.aux>0 && (car[i].mx!=-3 || player.On== 1)){
						oslPlaySound(crash,1);
						player.On=0;
						oslSetImageTileSize(player.image,0,32,64,32);	
						oslSetImageTileSize(car[i].image,(car[i].type-1)*64,32,64,32);	
						car[i].mx=-3;
					}
					for(int j=0;j<=20;j++)
						if(car[j].On==1 && i!=j && car[j].image&&1==1 && collision(car[i].image,car[j].image)==1 && (car[i].mx!=-3 || police.mx!=-3)){
							oslPlaySound(crash,1);
							car[i].mx=-3;
							oslSetImageTileSize(car[i].image,(car[i].type-1)*64,32,64,32);	
							car[j].mx=-3;
							oslSetImageTileSize(car[j].image,(car[j].type-1)*64,32,64,32);	
						}
					if(police.On == 1 && collision(car[i].image,police.image) == 1 && (car[i].mx!= -3 || police.mx!=-3)){
						oslPlaySound(crash,1);
						police.mx=-3;
						car[i].mx=-3;
						oslSetImageTileSize(police.image,police.type*64,32,64,32);	
						oslSetImageTileSize(car[i].image,(car[i].type-1)*64,32,64,32);
						oslStopSound(siren);
					}
				}
			}
			if(frame==-480)
				frame=0;
			else
				frame-=3;
			///////////////////////////////////////////////////////////////////////
			if(done==0){
				if(rand()%50==0)
					create_car(1);
				if(rand()%100==0)
					create_car(2);
				oslPrintf_xy(10,0,"Highscore: %d",hi[2]);
				oslPrintf_xy(120,90,"PRESS X TO START");
				oslPrintf_xy(120,110,"PRESS START FOR MENU");
				if(osl_pad.pressed.start)	{
					clvl=0;
					player.aux=0;
					break;
				}
				if(osl_pad.pressed.cross){
					player.aux=3;
					done=1;
				}
			}else if(done==1){
				for(int i=0;i<20;i++)
					car[i].On=0;
				//memset(car,0,sizeof (car));
				police.On=0;
				oslStopSound(siren);
				gas.On=0;
				gas.aux=1000;
				gas.mx=-3;
				player.On=1;
				player.image->x=480/2-32;
				player.image->y=272/2+16;
				oslSetImageTileSize(player.image,0,0,64,32);
				player.mx=0;
				player.my=0;
				player.image->angle=0;
				check=0;vlr=0;vud=0;
				for(int i=0;i<5;i++)	
					while(car[i].On==0)
						create_car(i%2+1);
				gas.frame=300;
				frame=0;
				if(player.aux>0)
					done=2;
				else{
					done=0;
					if(hi[2]<score)
						hi[2]=score;
					score=0;
				}
			}else if(done==2){
				if(osl_pad.pressed.start)	{
					pause=1;
					continue;
				}
				if(rand()%(70-score/200)==0)
					create_car(1);
				if(rand()%(200-score/200)==0)
					create_car(2);
				if((rand()%(800-score/30)==0 ||  osl_pad.pressed.triangle) &&  police.On==0 )	{
					oslSetSoundLoop(siren,1);
					oslPlaySound(siren,2);
					police.On=1;
					oslSetImageTileSize(police.image,0,0,64,32);
					police.image->x=-64;
					police.image->y=player.image->y;
					police.mx=2;
					police.aux=10;
					police.type=0;
				}
				oslDrawImage(player.image);
				if(gas.On){
					oslDrawImage(gas.image);
					gas.update();
				}
				if(police.On==1){
					if(collision(police.image,player.image)==1 && (player.On==1 || police.mx !=-3)){
						oslPlaySound(crash,1);
						player.On=0;
						oslSetImageTileSize(player.image,0,32,64,32);	
						oslSetImageTileSize(police.image,police.type*64,32,64,32);	
						police.mx=-3;
						oslStopSound(siren);
					}
					oslDrawImage(police.image);
					police.image->x+=police.mx;
					if(police.mx!=-3){
						if(police.image->y>player.image->y)
							police.image->y-=2;
						if(police.image->y<player.image->y)
							police.image->y+=2;
						if(police.aux>0){
							police.aux--;
						}else if(police.aux==0){
							police.type=!police.type;
							police.aux=10;
							oslSetImageTileSize(police.image,64*police.type,0,64,32);
						}
					}
					if(police.is_off_screen()==1 && (police.image->x>480 || police.mx==-3)){
						score+=500;
						police.On=0;
					}
				}
				if(player.On==1){
					vlr=-osl_pad.held.right+osl_pad.held.left;
					vud=-osl_pad.held.down+osl_pad.held.up;
					if ((player.my==3 && osl_pad.held.up) || (player.my==-3 && osl_pad.held.down))
						check=1;
					if(abs(vud) == 1 && check == 0){
						double aux=0.3*vud;
						if(fabs(player.my+aux)<3 && aux<1)
							player.my+=aux;
					}else if(check == 1)
						vud = 0;
					if(abs(vlr) == 1){
						double aux=0.3*vlr;
						if((player.mx+aux<=2 && vlr==1) || (player.mx+aux>=-4 && vlr==-1))
							player.mx+=aux;
					}
					if (fabs(player.mx + player.my)>0){
						player.image->x+=player.mx;
						player.image->y+=player.my;
						player.image->angle=player.my*3;
					}
					else
						player.image->angle=0;
					if (vlr==0){
						int aux = (player.mx>=0)?(1):(-1);
						player.mx-=0.4*aux;
						if (fabs(player.mx)<=0.4){
							player.mx=0;
						}
					}
					if (vud==0){
						int aux = (player.my>=0)?(1):(-1);
						player.my-=0.4*aux;
						if (fabs(player.my)<=0.4){
							player.my=0;
						}
					}
					if(gas.aux==0)
						player.On=0;
					gas.aux--;
					score++;
				}
				if(gas.frame==0){
					gas.On=1;
					gas.image->x=560;
					gas.image->y=rand()%200;
					gas.frame=300+score/100;
				}
				else
					gas.frame--;
				if(gas.image->x<480 && gas.is_off_screen())
					gas.On=0;
				if(collision(player.image,gas.image) && gas.On==1){
					gas.On=0;
					gas.aux+=400;
					if(gas.aux>1000)
						gas.aux=1000;
				}
				oslPrintf_xy(10,0,"Lives:%d Score: %d Highscore: %d",player.aux,score,hi[2]);
				oslPrintf_xy(10,20,"GAS:");
				oslDrawHealthBar(50,20,100,20,gas.aux,1000,1);
				if(player.is_off_screen()){
					player.aux--;
					done=1;
				}
				if(player.On==0)
					player.image->x-=3;	
			}
			////////////////////////////////////////////////////////////////
		}else{
			oslDrawImageXY(title[12],frame,0);
			oslDrawImageXY(title[12],frame+480,0);
			for(int i=0;i<=20;i++)
				if(car[i].On==1)
					oslDrawImage(car[i].image);
			oslDrawImage(player.image);
			if(gas.On)
				oslDrawImage(gas.image);
			if(police.On==1)
				oslDrawImage(police.image);
			oslPrintf_xy(10,0,"Lives:%d Score: %d Highscore: %d",player.aux,score,hi[2]);
			oslPrintf_xy(10,20,"GAS:");
			oslDrawHealthBar(50,20,100,20,gas.aux,1000,1);
			oslPrintf_xy(120,90,"PRESS X TO CONTINUE");
			oslPrintf_xy(120,110,"PRESS O FOR MENU");
			if(osl_pad.pressed.circle)	{
				clvl=0;
				player.aux=0;
				break;
			}
			if(osl_pad.pressed.cross){
				pause=0;
			}
		}
		if(score==6000 && ac[8]==0)
			fnc_achievements(8);
		DrawAchievement();
		oslEndDrawing();
		oslSyncFrame();
	}
	oslDeleteImage(gas.image);
	oslDeleteImage(player.image);
	oslDeleteImage(police.image);
	oslDeleteSound(crash);
	oslDeleteSound(siren);
	oslSetTextColor(black);
	oslSetFont(font);
	return 0;
}