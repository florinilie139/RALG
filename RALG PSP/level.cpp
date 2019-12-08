void controls ()
{
	plus=8;
	if(osl_pad.held.triangle)
		plus=2;
	if (osl_pad.held.up && mouse->y>=plus)
		mouse->y-=plus;
	if (osl_pad.held.down && mouse->y<=272-(plus+16))
		mouse->y+=plus;
	if (osl_pad.held.left && mouse->x>=plus)
		mouse->x-=plus;
	if (osl_pad.held.right&& mouse->x<=480-(plus+16))
		mouse->x+=plus;
	oslDrawImage(mouse);
}
void engine()
{
	for(int i=1;i<=maxobj;i++)
		if(obj[i].On==1){
			obj[i].update();
			oslDrawImage(obj[i].image);
			obj[i].texting();
			if(obj[i].touched()==1)
				touch=i;
			if(obj[i].moving()==1)
				move=i;
			obj[i].debug(i);
		}
	if(debugON==2)
		debugON=1;
	if(osl_pad.pressed.cross && touch==0)
		touch = -1;
	if(plus==0){
		plus=8;
		if(osl_pad.held.triangle)
			plus=2;
	}
	if (osl_pad.held.up    && mouse->y >= plus)
		mouse->y-=plus;
	if (osl_pad.held.down  && mouse->y <= 272-(plus+16))
		mouse->y+=plus;
	if (osl_pad.held.left  && mouse->x >= plus)
		mouse->x-=plus;
	if (osl_pad.held.right && mouse->x <= 480-(plus+16))
		mouse->x+=plus;
	plus=0;
	if(move!=0)
	{
		obj[move].image->x = mouse->x - obj[move].image->sizeX/2;
		obj[move].image->y = mouse->y - obj[move].image->sizeY/2;
		if(move_enable==1 && osl_pad.pressed.square){
			lmove=move;
			move=0;
		}
	}
	if(move==0 ||(move!=0 && draw_mouse==0))
		oslDrawImage(mouse);
}
void erase ()
{
	for(int i=1;i<=maxobj;i++)
		if(obj[i].image!=0)
			oslDeleteImage(obj[i].image);
	for(int i=1;i<=maxobj;i++)
		memset(&obj[i], 0, sizeof(obj[i]));
	draw_mouse=0;
	move_enable=0;
	maxobj=0;
	frame=0;
	touch=0;
	move=0;
	lmove=0;
	atime=0;
}
void randlvl ()
{
	if(rndlvl==1){
		random_shuffle(lvl+1,lvl+6);
		random_shuffle(lvl+6,lvl+11);
	}else if (rndlvl==2)
		random_shuffle(lvl+1,lvl+11);
	else
		sort(lvl+1,lvl+15);
}
void level ()
{
	switch(lvl[clvl]){
		case 1:
			if(done==2)
			{
				oslDrawImage(title[4]);
				if(frame<3)
					oslPrintf_xy(11,10,LvL1Details[1]);
				else
					oslPrintf_xy(11,10,LvL1Details[frame-1]);
				if(frame==7)
				{
					if(atime==0){
						lose=1;
					}
					atime-=seconds;
					//oslPrintf_xy(11,20,"time: %d",atime);
				}
				if((touch==1 && (frame<3 || frame==5 || frame==7))||(touch==-1 && (frame==3 || frame==4 || frame==6))){
					frame++;
					done=1;
					touch=0;
				}
				else if(touch==1 && (frame==3 || frame==4 || frame==6)){
					touch=0;
					lose=1;
				}
			}else{
				done=2;
				switch(frame){
					case 0:
						maxobj=1;
						oslSetTextColor(white);
						obj[1].On=1;
						obj[1].image=oslCreateImageCopy(button[0],OSL_IN_RAM);
						break;
					case 4:
						oslDeleteImage(obj[1].image);
						obj[1].image=oslCreateImageCopy(button[1],OSL_IN_RAM);
						break;
					case 5:
						oslDeleteImage(obj[1].image);
						obj[1].image=oslCreateImageCopy(button[2],OSL_IN_RAM);
						break;
					case 6:
						oslDeleteImage(obj[1].image);
						obj[1].image=oslCreateImageCopy(button[3],OSL_IN_RAM);
						break;
					case 7:
						atime = 3;
						oslDeleteImage(obj[1].image);
						obj[1].image=oslCreateImageCopy(button[1],OSL_IN_RAM);
						break;
				}
				obj[1].image->x = (rand()%10+1)*40;
				obj[1].image->y = (rand()%10+1)*20;
				if(frame==8){
					oslSetTextColor(black);
					erase();
					clvl++;
					done=1;
				}
			}
			break;
		case 2:
			if(done==2)
			{
				oslDrawImage(title[2]);
				for(int i=1;i<=2;i++)
					oslPrintf_xy(11,10*i,LvL2Details[i]);
				oslDrawFillRect(obj[2].fx1, obj[2].fy1, obj[2].fx2, obj[2].fy2, green);
				oslDrawFillRect(obj[3].fx1, obj[3].fy1, obj[3].fx2, obj[3].fy2, blue);
				oslDrawFillRect(obj[4].fx1, obj[4].fy1, obj[4].fx2, obj[4].fy2, red);
				oslDrawFillRect(obj[5].fx1, obj[5].fy1, obj[5].fx2, obj[5].fy2, yellow);
				if(move==0){
					for(int i=2;i<=5;i++){
						if((obj[1].image->x + obj[1].image->stretchX > obj[i].fx1) && (obj[1].image->x < obj[i].fx2) && (obj[1].image->y + obj[1].image->stretchY > obj[i].fy1) && (obj[1].image->y < obj[i].fy2) ){
							if(obj[i].aux==1){
								obj[1].aux=2;
								break;
							}else{
								obj[1].aux=1;
								break;
							}
						}
					}
					if(obj[1].aux==2){
						erase();
						clvl++;
						done=1;
					}else if(obj[1].aux==1)
						lose=1;
				}
			}else	{
				move_enable=1;
				maxobj=5;
				obj[1].image=oslCreateImageCopy(graphics[1],OSL_IN_RAM);
				obj[1].On=1;
				obj[1].image->x=50;
				obj[1].image->y=20;
				obj[1].moveble=1;
				int aux=rand()%4+1;
				obj[aux+1].aux=1;
				for(int i=1;i<=4;i++){
					if(i!=aux){
						int aux1=(rand()%6)*10+64,aux2=0;
						obj[i+1].fx1=(120-aux1)/2+(i-1)*120;
						obj[i+1].fx2=obj[i+1].fx1+aux1;
						do{
							aux2=(rand()%6)*10+64;
						}while(aux1==aux2);
						obj[i+1].fy1=(200-aux2)/2+81;
						obj[i+1].fy2=obj[i+1].fy1+aux2;
					}
					else{
						int aux1=(rand()%6)*10+64;
						obj[i+1].fx1=(120-aux1)/2+(i-1)*120;
						obj[i+1].fx2=obj[i+1].fx1+aux1;
						obj[i+1].fy1=(200-aux1)/2+81;
						obj[i+1].fy2=obj[i+1].fy1+aux1;
					}
				}
				done=2;
			}
			break;
		case 3:
			if(done==2)
			{
				oslDrawImage(title[4]);
				for(int i=1;i<=2;i++)
					oslPrintf_xy(11,10*i,LvL3Details[i]);
				if(touch==1){
					erase();
					clvl++;
					done=1;
					oslSetTextColor(black);
				}else if(touch==2)
					lose=1;
			}else
			{
				maxobj=2;
				obj[1].On=1;	obj[1].image=oslCreateImageCopy(graphics[1],OSL_IN_RAM);	obj[1].bounce=1;	obj[1].image->x=0;		obj[1].image->y=104;	obj[1].mx=18;
				obj[2].On=1;	obj[2].image=oslCreateImageCopy(graphics[2],OSL_IN_RAM);	obj[2].bounce=1;	obj[2].image->x=208;	obj[2].image->y=0;		obj[2].mx=14;	obj[2].my=12;
				done=2;
				oslSetTextColor(white);
			}
			break;
		case 4:
			if(done==2)
			{
				oslDrawImage(title[2]);
				for(int i=1;i<=3;i++)
					oslPrintf_xy(11,10*i,LvL4Details[i]);
				if(lmove!=0 ){
					if(frame!=1 && obj[lmove].image->x>=300 && obj[lmove].image->x+64<=390 && obj[lmove].image->y>=20+100*((lmove-1)%2) && obj[lmove].image->y+64<=10+100*((lmove-1)%2+1)){
						obj[lmove].On=0;
						obj[3].aux++;
					}
					lmove=0;
				}
				if(frame==0){
					oslDrawFillRect(300,20,390,110,blue);
					if(obj[3].aux==4){
						frame=1;
						done=1;
					}
				}else if(frame==1){
					if(atime==0)
					{
						frame++;
						done=1;
					}
					atime-=seconds;
					//oslPrintf_xy(11,40,"time: %d",atime);
				}else{
					oslDrawFillRect(300,20,390,110,blue);
				}
				if(touch==3)
				{
					if(obj[3].aux==6){
						erase();
						clvl++;
						done=1;
					}else
						lose=1;
				}
			}else	{
				if(frame==0){
					move_enable=1;
					maxobj=9;
					for(int i=4;i<=9;i++){
						obj[i].On=1;
						obj[i].image=oslCreateImageCopy(graphics[3+(i-1)%2],OSL_IN_RAM);
						obj[i].image->x=14;
						obj[i].image->y=80*((i-1)%2+1);
						obj[i].moveble=1;
					}
					obj[1].On=0;	obj[1].image=oslCreateImageCopy(graphics[5],OSL_IN_RAM);	obj[1].image->x=300;	obj[1].image->y=20;
					obj[2].On=1;	obj[2].image=oslCreateImageCopy(graphics[7],OSL_IN_RAM);	obj[2].image->x=300;	obj[2].image->y=120;
					obj[3].On=1;	obj[3].image=oslCreateImageCopy(graphics[8],OSL_IN_RAM);	obj[3].image->x=300;	obj[3].image->y=222;
				}else if(frame==1)
				{
					obj[1].On=1;
					oslDeleteImage(obj[2].image);
					obj[2].image=oslCreateImageCopy(graphics[6],OSL_IN_RAM); obj[2].image->x=300;	obj[2].image->y=120;
					atime=10;
				}else{
					obj[1].On=0;
					oslDeleteImage(obj[2].image);
					obj[2].image=oslCreateImageCopy(graphics[7],OSL_IN_RAM); obj[2].image->x=300;	obj[2].image->y=120;
				}
				done=2;
			}
			break;
		case 5:
			if(done==2)
			{
				oslDrawImage(title[5]);
				oslPrintf_xy(11,10,LvL5Details[frame+1]);
				if(osl_pad.pressed.cross && mouse->x>20 && mouse->x<80 && mouse->y>10 &&  mouse->y<20)
				{
					if(ac[5]==0)
						fnc_achievements(5);
					erase();
					clvl++;
					done=1;
					break;
				}
				if(touch==1)
					lose=1;
				if(atime==2)
					obj[1].text=1;
				if(atime==0){
					frame++;
					done=1;
					if(frame==2){
						erase();
						clvl++;
						done=1;
					}
				}
				atime-=seconds;
			}else{
				maxobj=1;
				obj[1].text=0;
				if(frame==0){
					obj[1].On=1;
					obj[1].image=oslCreateImageCopy(button[3],OSL_IN_RAM);
					strcpy(obj[1].txt,"Press me!");
					obj[1].tx=5; obj[1].ty=20;
					obj[1].image->x=208; obj[1].image->y=104;
				}else{
					obj[1].image->x=70; obj[1].image->y=100;
				}
				atime=7;
				done=2;
			}
			break;
		case 6:
			if(done==2)
			{
				oslDrawImage(title[4]);
				if(touch==1){
					if(obj[1].aux==0)
						obj[1].On=0;
					obj[1].aux--;
					sprintf(obj[1].txt,"%d",obj[1].aux);
					if(ac[6]==0 && obj[1].aux==0){
						fnc_achievements(6);
					}
					touch=0;
				}
				if(touch==2){
					erase();
					oslSetTextColor(black);
					clvl++;
					done=1;
				}
				if(frame==0 && obj[1].aux==970){
					obj[2].On=1;
					frame=1;
				}else if(frame==1)
					oslPrintf_xy(11, 10,LvL6Details);
			}else{
				maxobj=2;
				obj[1].On=1;		obj[1].image=oslCreateImageCopy(graphics[7],OSL_IN_RAM);		obj[1].image->x=195;	obj[1].image->y=91;	obj[1].aux=999; obj[1].text=1; sprintf(obj[1].txt,"%d",obj[1].aux); obj[1].tx=33; obj[1].ty=37;	obj[1].big=1;
				obj[2].On=0;	obj[2].image=oslCreateImageCopy(graphics[8],OSL_IN_RAM);	obj[2].image->x=300;	obj[2].image->y=222;
				done=2;
				oslSetTextColor(white);
			}
			break;
		case 7:
			if(done==2){
				oslDrawImage(title[6]);
				oslPrintf_xy(11,10,LvL7Details);
				for(int i=2;i<=5;i++)
					if(collision(obj[1].image,obj[i].image)){
						lose=1;
					}
				if(obj[1].image->y<10)
				{
					atime-=seconds;
					if(frame==0||atime==0){
						frame++;
						done=1;
					}
				}
				else
					plus=2;
			}else{
				if(frame==0){
					maxobj=5;
					obj[1].image = oslCreateImageCopy(graphics[9] ,OSL_IN_RAM);
					obj[2].image = oslCreateImageCopy(graphics[10],OSL_IN_RAM);
					obj[3].image = oslCreateImageCopy(graphics[11],OSL_IN_RAM);
					obj[4].image = oslCreateImageCopy(graphics[12],OSL_IN_RAM);
					obj[5].image = oslCreateImageCopy(graphics[13],OSL_IN_RAM);
					oslSetImageTileSize(obj[2].image, 0, 0,64,32);
					oslSetImageTileSize(obj[3].image, 0, 0,64,32);
					oslSetImageTileSize(obj[4].image,64, 0,64,32);
					oslSetImageTileSize(obj[5].image,64, 0,64,32);
					obj[1].On=1;	mouse->x=190;	mouse->y=253;
					obj[2].On=1;	obj[2].image->x=480;	obj[2].image->y= 69;	obj[2].bounce=2;	obj[2].mx=-8;
					obj[3].On=1;	obj[3].image->x=480;	obj[3].image->y= 24;	obj[3].bounce=2;	obj[3].mx=-10;
					obj[4].On=1;	obj[4].image->x=  0;	obj[4].image->y=204;	obj[4].bounce=2;	obj[4].mx=4;
					obj[5].On=1;	obj[5].image->x=  0;	obj[5].image->y=155;	obj[5].bounce=2;	obj[5].mx=6;
					draw_mouse=1;
					move_enable=0;
					move=1;
					done=2;
					oslSetTextColor(white);
				}else if(frame==1){
					draw_mouse=0;
					move_enable=0;
					move=0;
					atime=5;
					done=2;
				}else{
					erase();
					oslSetTextColor(black);
					clvl++;
					done=1;
				}
			}
			break;
		case 8:
			if(done==2){
				oslDrawImage(title[4]);
				oslPrintf_xy(11,10,LvL8Details);
				if(touch==3){
					erase();
					oslSetTextColor(black);
					clvl++;
					done=1;
				}else if(touch>0)
					lose=1;
			}else{
				maxobj=3;
				obj[1].On=1;	obj[2].On=1;	obj[3].On=1;
				obj[1].image = oslCreateImageCopy(graphics[14],OSL_IN_RAM);
				obj[2].image = oslCreateImageCopy(graphics[15],OSL_IN_RAM);
				obj[3].image = oslCreateImageCopy(graphics[16],OSL_IN_RAM);
				obj[1].image->x=50;		obj[1].image->y=120;
				obj[2].image->x=200;	obj[2].image->y=120;
				obj[3].image->x=350;	obj[3].image->y=120;
				oslSetTextColor(white);
				done=2;
			}
			break;
		case 9:
			if(done==2){
				oslDrawImage(title[5]);
				oslPrintf_xy(11,10,LvL9Details[frame]);
				if(touch==-1 || atime==0){
					done=1;
					touch=0;
				}else if(touch==1)
					lose=1;
				atime-=seconds;
			}else{
				maxobj=1;
				done=2;
				if(frame==0){
					obj[1].On=1;
					obj[1].image = oslCreateImageCopy(graphics[17],OSL_IN_RAM);
					obj[1].image->x=170; obj[1].image->y=90;
					frame=1;
					oslSetTextColor(white);
					atime=3;
				}else if(frame==1){
					oslDeleteImage(obj[1].image);
					obj[1].image = oslCreateImageCopy(graphics[18],OSL_IN_RAM);
					obj[1].image->x=170; obj[1].image->y=90;
					atime=3;
					frame=2;
				}else{
					erase();
					oslSetTextColor(black);
					clvl++;
					done=1;
				}
			}
			break;
		case 10:
			if(done>=2)
			{
				oslDrawImage(title[2]);
				if(atime>=60 && atime<=90)
					oslPrintf_xy(11,10,LvL10Details[1]);
				else if(atime<=30)
					oslPrintf_xy(11,10,LvL10Details[2]);
				oslDrawFillRect(160,12,320,44,gray);
				oslDrawFillRect(165,17,315,39,green);
				oslSetFont(big_font);
				for(int a=0;a<5;a+=2){
					for(int b=0;b<5;b+=2){
						oslDrawFillRect(160+32*b,64+32*a-16,160+32*(b+1),80+32*a,gray);
						oslPrintf_xy(160+32*b+12,64+32*a-8,"%d",((3*a/2)+b/2+1));
					}
				}
				oslDrawFillRect(160,240,192,272,gray);
				oslPrintf_xy(172,248,"0");
				oslDrawFillRect(224,240,320,272,gray);
				oslPrintf_xy(246,248,LvL10Details[3]);
				oslPrintf_xy((240-(strlen(obj[0].txt)*4)),20,obj[0].txt);
				oslSetFont(font);
				if(osl_pad.pressed.cross){
					if(strlen(obj[0].txt)>4 || (mouse->x>=128+32 && mouse->x<=128+64 && mouse->y>=64+32*6-16 && mouse->y<=64+32*7-16))
						obj[0].txt[0]=0;
					if(strlen(obj[0].txt)!=4)
						for(int a=0;a<5;a+=2)
							for(int b=0;b<5;b+=2)
									if(mouse->x>=128+32*(b+1) && mouse->x<=128+32*(b+1)+32 && mouse->y>=64+32*a-16 && mouse->y<=64+32*a+16)
										sprintf(obj[0].txt+strlen(obj[0].txt),"%c",(char)(((3*a/2)+b/2+1)+'0'));
					if(mouse->x>=128+64+32 && mouse->x<=128+64+32+96 && mouse->y>=64+32*6-16 && mouse->y<=64+32*6-16+32){
						if(strcmp("4164",obj[0].txt)==0)	{
							erase();
							clvl++;
							done=1;
						}else
							obj[0].txt[0]=0;
					}
				}
				if(atime>0)
					atime-=seconds;
			}else{
				strcpy(obj[0].txt,LvL10Details[0]);
				atime=120;
				done=2;
			}
			break;
		case 11:
			oslDrawImage(title[11]);
			if(osl_pad.pressed.cross || osl_pad.pressed.circle){
				done=0;
				state='m';
			}
			break;
	}
	oslPrintf_xy(11,0,"Level: %d",clvl);
	engine();
}

void inflevel()
{
	switch(clvl){
		case 1:
			break;
		case 2:
			street_main();
			erase();
			break;
		case 3:
			oslSetFont(big_font);
			//CI_start();
			oslSetFont(font);
			break;
		default:
			break;
	}
	state='m';
	done=0;
}