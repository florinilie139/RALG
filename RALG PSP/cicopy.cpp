#include <oslib/oslib.h>

FILE* debug;
OSL_IMAGE *space,*CI_title,*CI_select,*ship,*bullets[10],*CI_chickens,*sprites[20],*CI_HUD,*CI_boss, *CI_effects;
OSL_SOUND *CI_music[4],*CI_sounds[20];
int CI_exit,option,space_warp=1,shipX=1,shipY=1,wait_fire,wait_fire_max=25,power,type,nr_level=0,difficulty,chickens_on_level,chicken_move_direction=1,respawn_invin,level_cooldown_timer,eat_food,ammo_bomb,CI_bomb[10],current_score,displayed_score,lives,lives_points,combo_time,combo_multi;
double obj_bullets[50][20];
double obj_chickens[50][20];
double obj_eggs[40][20];
double obj_present[20][20];
double obj_food[20][20];
double obj_boss[20][20];
char stace[30]="menu";
double obj_effects[20][10];



void initializer ();
void RESET ();
void UNLOAD ();
void CI_menu();
void CI_pause();
void CI_game();
void do_points();
void ship_ctrl();
void scroll_space();
void draw_graphics();
void update_eggs();
void update_presents();
void update_food();
void update_bullets();
void update_chickens();
void update_boss();
void update_efects();
void eats_food (int ftype);
void drop_food (int LocX,int LocY);
void shoot_bomb();
void shoot_bullet();
void set_levels ();
void move_chickens ();
void died ();
void respawn();
void create_food(double foodX,double foodY,double speed,int ftype,double fangle);
void create_present(double presentX,double presentY,double speed,int ptype);
void create_eggs(double eggsX,double eggsY,double speed);
void create_chicken(double chickenX,double chickenY,int ctype,int frame,int speed,int chealth);
void create_boss(double bossX,double bossY,int bosstype,int frame,int speed,int bhealth);
void create_bullet(double bulletX,double bulletY,double speedX,double speedY,int btype,double dmg,int blife);
void create_effects(int number,int effectX,int effectY,int effect_type,int effect_size,int eff_dirX,int eff_dirY);
void kill_chickens();
void remove_chickens();
void remove_eggs();

int CI_start()
{
	debug = fopen ("debugci.txt" , "w");
	initializer();
	RESET();
	while(CI_exit==0 && osl_quit!=1){
		oslStartDrawing();
		oslReadKeys();
		if(strcmp(stace,"menu")==0)
			CI_menu();
		if(strcmp(stace,"game")==0)
			CI_game();
		if(strcmp(stace,"pause")==0)
			CI_pause();
		oslEndDrawing();
		oslSyncFrame();
	}
	oslReadKeys();
	UNLOAD();
	fclose(debug);
	return 0;
}
void initializer ()
{
	CI_exit=0;
	oslSetTextColor(RGB(255,255,255));
	space = oslLoadImageFilePNG("graphics/space.png",OSL_IN_RAM,OSL_PF_5551);
	ship = oslLoadImageFilePNG("graphics/ship.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[0] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);		sprites[1] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[2] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);		sprites[3] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[4] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);		sprites[5] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[6] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);		sprites[7] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[8] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);		sprites[9] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[10] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);	sprites[11] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);
	sprites[12] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);	sprites[13] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551); 
	sprites[14] = oslLoadImageFilePNG("graphics/sprites_CI.png",OSL_IN_RAM,OSL_PF_5551);	CI_boss = oslLoadImageFilePNG("graphics/boss.png",OSL_IN_RAM,OSL_PF_5551);
	bullets[0] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);		bullets[1] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);
	bullets[2] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);		bullets[3] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);
	bullets[4] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);		bullets[5] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);
	bullets[6] = oslLoadImageFilePNG("graphics/bullets.png",OSL_IN_RAM,OSL_PF_5551);		CI_chickens = oslLoadImageFilePNG("graphics/chickens.png",OSL_IN_RAM,OSL_PF_5551);
	CI_title = oslLoadImageFilePNG("graphics/CI_title.png",OSL_IN_RAM,OSL_PF_5551);			CI_select = oslLoadImageFilePNG("graphics/select.png",OSL_IN_RAM,OSL_PF_5551);
	CI_HUD = oslLoadImageFilePNG("graphics/HUD.png",OSL_IN_RAM,OSL_PF_5551);				CI_effects = oslLoadImageFilePNG("graphics/CI_effects.png",OSL_IN_RAM,OSL_PF_5551);	
	CI_music[0] = oslLoadSoundFileBGM("sounds/main_theme.bgm",OSL_FMT_STREAM);				CI_sounds[0] = oslLoadSoundFileWAV("sounds/fire1.wav", OSL_FMT_NONE);
	CI_sounds[1] = oslLoadSoundFileWAV("sounds/kill.wav", OSL_FMT_NONE);					CI_sounds[2] = oslLoadSoundFileWAV("sounds/egg_splat.wav", OSL_FMT_NONE);
	CI_sounds[3] = oslLoadSoundFileWAV("sounds/eggsplsion.wav", OSL_FMT_NONE);				CI_sounds[4] = oslLoadSoundFileWAV("sounds/present.wav", OSL_FMT_NONE);
	CI_sounds[5] = oslLoadSoundFileWAV("sounds/eat_food.wav", OSL_FMT_NONE);				CI_sounds[6] = oslLoadSoundFileWAV("sounds/hitboss.wav", OSL_FMT_NONE);
	CI_sounds[7] = oslLoadSoundFileWAV("sounds/dboss.wav", OSL_FMT_NONE);					CI_sounds[8] = oslLoadSoundFileWAV("sounds/rock death.wav", OSL_FMT_NONE);
	CI_sounds[9] = oslLoadSoundFileWAV("sounds/fire2.wav", OSL_FMT_NONE);					CI_sounds[10] = oslLoadSoundFileWAV("sounds/fire3.wav", OSL_FMT_NONE);
	oslSetImageTileSize(sprites[0],0,0,33,27);		oslSetImageTileSize(sprites[1],33*2,0,33,27);
	oslSetImageTileSize(sprites[2],33,0,33,27);		oslSetImageTileSize(sprites[3],33*3,0,33,27);
	oslSetImageTileSize(sprites[4],33*4,0,33,27);	oslSetImageTileSize(sprites[5],33*5,0,33,27);
	oslSetImageTileSize(sprites[6],33*6,0,33,27);	oslSetImageTileSize(sprites[7],33*7,0,33,27);
	oslSetImageTileSize(sprites[8],33*8,0,33,27);	oslSetImageTileSize(sprites[9],33*9,0,33,27);
	oslSetImageTileSize(sprites[10],33*10,0,33,27);	oslSetImageTileSize(sprites[11],33*11,0,33,27);
	oslSetImageTileSize(sprites[12],33*12,0,33,27);	oslSetImageTileSize(sprites[13],33*13,0,33,27);
	oslSetImageTileSize(sprites[14],33*14,0,33,27); oslSetImageTileSize(CI_boss,0,0,104,83);
	oslSetImageTileSize(bullets[0],0,0,7,32);		oslSetImageTileSize(bullets[1],7,0,4,31);
	oslSetImageTileSize(bullets[2],11,0,12,31);		oslSetImageTileSize(bullets[3],23,0,14,31);	
	oslSetImageTileSize(bullets[4],0,32,13,6);		oslSetImageTileSize(bullets[5],0,38,25,8);	
	oslSetImageTileSize(bullets[6],0,46,25,8);		oslSetImageTileSize(ship,shipX*43,shipY*48,43,48);
	for(int i=1;i<=8;i++){
		sprites[i+6]->centerX=33/2;
		sprites[i+6]->centerY=27/2;
	}
	CI_title->x=81;		CI_title->y=8;
	CI_select->x=176;	CI_select->y=140;
	CI_boss->centerX=52; CI_boss->centerY=41;
	difficulty=1;
}
void RESET (){
	option=0;
	for(int i=0;i<=50;i++){
		for(int j=0;j<=8;j++)
			obj_bullets[i][j]=0;
	}
	for(int i=0;i<=10;i++){
		for(int j=0;j<=5;j++)
			obj_present[i][j]=0;
	}
	remove_chickens();
	remove_eggs();
	for(int i=0;i<=20;i++){
		for(int j=0;j<=6;j++)
			obj_food[i][j]=0;
	}
	for(int i=0;i<=5;i++){
		for(int j=0;j<=10;j++)
			obj_boss[i][j]=0;
	}
	eat_food=0;
	nr_level=0;
	wait_fire=0;
	wait_fire_max=25;
	power=1;
	type=1;
	ship->x=215;ship->y=200;
	chickens_on_level=0;
	difficulty=1;
	respawn_invin=0;
	ammo_bomb=0;
	oslReadKeys();
	current_score=0;
	displayed_score=0;
	lives=3;
	lives_points=0;
	combo_time=0;
	combo_multi=1;
	level_cooldown_timer=100;
}
void UNLOAD ()
{
	oslDeleteImage(space);
	oslDeleteImage(ship);
	for(int i=0;i<=14;i++)
		oslDeleteImage(sprites[i]);
	for(int i=0;i<=6;i++)
		oslDeleteImage(bullets[i]);
	oslDeleteImage(CI_boss);
	oslDeleteImage(CI_chickens);
	oslDeleteImage(CI_title);
	oslDeleteImage(CI_select);
	oslDeleteImage(CI_HUD);
	oslDeleteSound(CI_music[0]);
	for(int i=0;i<=10;i++)
		oslDeleteSound(CI_sounds[i]);
}
void CI_menu()
{
	scroll_space();
	oslDrawImage(CI_title);
	oslPrintf_xy(215,144,"START");
	oslPrintf_xy(205,192,"Highscore");
	oslPrintf_xy(225,240,"Exit");
	oslDrawImage(CI_select);
	if(osl_pad.pressed.cross && CI_select->y==140+option*48){
		switch(option){
			case 0:
				strcpy(stace,"game");
				RESET();
				nr_level=-1;
				space_warp=150;
				oslReadKeys();
				break;
			case 1:
				break;
			case 2:
				CI_exit=1;
				oslStopSound(CI_music[0]);
				break;
		}
	}
	if(osl_pad.pressed.circle)
		CI_exit=1, oslStopSound(CI_music[0]);
	if(oslGetSoundChannel(CI_music[0])==-1)
		oslPlaySound(CI_music[0],0);
	if(osl_pad.pressed.down && option!=2)
		option++;
	if(osl_pad.pressed.up && option!=0)
		option--;
	if(CI_select->y<140+option*48)
		CI_select->y+=2;
	if(CI_select->y>140+option*48)
		CI_select->y-=2;
}
void CI_pause()
{
	scroll_space();
	oslPrintf_xy(215,144,"Continue");
	oslPrintf_xy(205,192,"MainMenu");
	oslDrawImage(CI_select);
	if(osl_pad.pressed.cross && CI_select->y==140+option*48){
		switch(option){
			case 0:
				strcpy(stace,"game");
				break;
			case 1:
				strcpy(stace,"menu");
				space_warp=1;
				break;
		}
	}
	if(osl_pad.pressed.circle)
		strcpy(stace,"game");
	if(osl_pad.pressed.down && option!=1)
		option++;
	if(osl_pad.pressed.up && option!=0)
		option--;
	if(CI_select->y<140+option*48)
		CI_select->y+=2;
	if(CI_select->y>140+option*48)
		CI_select->y-=2;
}
void CI_game()
{
	do_points();
	ship_ctrl();
	draw_graphics();
	set_levels();
	move_chickens();
	if(osl_pad.pressed.start){
		if(lives==0)
			strcpy(stace,"menu");
		else
			strcpy(stace,"pause");
	}
}
void do_points(){
	if (current_score - displayed_score + 3000 > 10000) displayed_score = displayed_score + 3000;
	if (current_score - displayed_score + 300  >  1000) displayed_score = displayed_score + 300 ;
	if (current_score - displayed_score + 30   >   100) displayed_score = displayed_score + 30  ;
	if (current_score - displayed_score		   >    10) displayed_score = displayed_score + 3   ;
	if (current_score < displayed_score)
		displayed_score=current_score; 
	if (displayed_score/1000000 > lives_points) {
		lives = lives + 1;
		lives_points = lives_points +1;
	}
}
void ship_ctrl()
{
	if(lives>0){
		if(respawn_invin==0){
			if ((osl_pad.held.up || osl_pad.analogY<-80) && ship->y>=2){
				ship->y-=5;
				shipY=0;
			}
			else if ((osl_pad.held.down || osl_pad.analogY>80)&& ship->y+49<=272-2){
				ship->y+=5;
				shipY=2;
			}
			else
				shipY=1;
		}
		else if(respawn_invin>0)
			respawn();
		if ((osl_pad.held.left || osl_pad.analogX<-80) && ship->x>=2){
			ship->x-=5;
			shipX=0;
		}
		else if ((osl_pad.held.right || osl_pad.analogX>80) && ship->x+43<=480-2){
			ship->x+=5;
			shipX=2;
		}
		else
			shipX=1;
		wait_fire--;
		if(wait_fire==wait_fire_max-5 && (type==1 || type==3))
			ship->y-=5;
		if(wait_fire==1 && type==2)
			ship->y-=3;
		if(osl_pad.held.cross)
			shoot_bullet();
		if(osl_pad.pressed.square)
			shoot_bomb();
	}
	if(osl_pad.pressed.select){
		fprintf(debug,"Level=%d\n",(difficulty-1)*10+nr_level%10);
		fprintf(debug,"space_warp=%d\n",space_warp);
		fprintf(debug,"wait_fire=%d\n",wait_fire);
		fprintf(debug,"wait_fire_max=%d\n",wait_fire_max);
		fprintf(debug,"difficulty=%d\n",difficulty);
		fprintf(debug,"chickens on level=%d\n",chickens_on_level);
		fprintf(debug,"power=%d\n",power);
		fprintf(debug,"type=%d\n",type);
		fprintf(debug,"\nbullets\n");
		for(int i=0;i<=40;i++){
			for(int j=0;j<=5;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_bullets[i][j]);
			fprintf(debug,"\n");
		}
		fprintf(debug,"\neggs\n");
		for(int i=0;i<=40;i++){
			for(int j=0;j<=3;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_eggs[i][j]);
			fprintf(debug,"\n");
		}
		fprintf(debug,"\npresents\n");
		for(int i=0;i<=10;i++){
			for(int j=0;j<=4;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_present[i][j]);
			fprintf(debug,"\n");
		}
		fprintf(debug,"\nchickens\n");
		for(int i=0;i<=40;i++){
			for(int j=0;j<=7;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_chickens[i][j]);
			fprintf(debug,"\n");
		}
		fprintf(debug,"\nfood\n");
		for(int i=0;i<=20;i++){
			for(int j=0;j<=6;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_food[i][j]);
			fprintf(debug,"\n");
		}
		fprintf(debug,"\nboss\n");
		for(int i=0;i<=5;i++){
			for(int j=0;j<=10;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_boss[i][j]);
			fprintf(debug,"\n");
		}
		fprintf(debug,"bomb\n");
		for(int i=0;i<=10;i++){
			fprintf(debug,"%2d=%2d ",i,CI_bomb[i]);
		}
		fprintf(debug,"\neffects\n");
		for(int i=0;i<=20;i++){
			for(int j=0;j<=7;j++)
				fprintf(debug,"%2d.%2d=%3.2lf ",i,j,obj_effects[i][j]);
			fprintf(debug,"\n");
		}
	}
}
void scroll_space()
{
	space->y-=272;
	if(space->y>=0)
		space->y=-272;
	oslDrawImage(space);
	space->y+=272;
	oslDrawImage(space);
	space->y+=space_warp;
}
void draw_graphics()
{
	scroll_space();
	oslSetImageTileSize(ship,shipX*43,shipY*49,43,49);
	if(CI_bomb[0]==1){
		oslDrawImageXY(sprites[14],CI_bomb[1],CI_bomb[2]);
		sprites[14]->angle+=CI_bomb[3];
		if(CI_bomb[4]<0){
			kill_chickens();
			remove_eggs();
			CI_bomb[0]=0;
			oslPlaySound(CI_sounds[3],5);
		}
		CI_bomb[4]--;
	}
	update_eggs();
	update_presents();
	update_food();
	update_bullets();
	update_chickens();
	update_food();
	update_efects();
	if(lives>0)
		oslDrawImage(ship);
	else
		oslPrintf_xy(200,135,"GAME OVER");
	if(lives==0 && respawn_invin==0)
		strcpy(stace,"menu");
	oslDrawImage(CI_HUD);
	oslPrintf_xy( 27,250,"%d",lives);
	oslPrintf_xy( 65,250,"%d",power);
	oslPrintf_xy(110,250,"%d",eat_food);
	oslPrintf_xy(160,250,"%d",ammo_bomb);
	if(combo_multi>5)
		oslPrintf_xy(382,230,"X%d COMBO",combo_multi);
	oslPrintf_xy(470-int(log10(displayed_score)+1)*8,250,"%d",displayed_score);
	if(combo_time==0){
		combo_time=-1;
		combo_multi=1;
	}else if(combo_time>0)
		combo_time--;
}
void update_eggs()
{
	for(int i=1;i<=40;i++){
		if(obj_eggs[i][0]==1){
			oslDrawImageXY(sprites[0],obj_eggs[i][1],obj_eggs[i][2]);
			obj_eggs[i][2]+=obj_eggs[i][3];
			if(obj_eggs[i][2]>250){
				obj_eggs[i][0]=2;
				obj_eggs[i][3]=50;
				oslPlaySound(CI_sounds[2],3);
			}
			if(ship->x+ship->stretchX>obj_eggs[i][1]+11 && ship->x<obj_eggs[i][1]+22 && ship->y+ship->stretchY>obj_eggs[i][2]+5 && ship->y<obj_eggs[i][2]+20 && respawn_invin==0){
				died();
				combo_multi=1;
				combo_time=-1;
				obj_eggs[i][0]=0;
			}
		}
		if(obj_eggs[i][0]==2){
			oslDrawImageXY(sprites[1],obj_eggs[i][1],obj_eggs[i][2]);
			if(obj_eggs[i][3]==0)
				obj_eggs[i][0]=0;
			obj_eggs[i][3]--;
		}
	}
}
void update_presents()
{
	for(int i=1;i<=10;i++){
		if(obj_present[i][0]==1){
			oslDrawImageXY(sprites[int (obj_present[i][4])+3],obj_present[i][1],obj_present[i][2]);
			obj_present[i][2]+=obj_present[i][3];
			if(obj_present[i][2]>250){
				obj_present[i][0]=0;
			}
			if(ship->x+ship->stretchX>obj_present[i][1]+5 && ship->x<obj_present[i][1]+27 && ship->y+ship->stretchY>obj_present[i][2]+4 && ship->y<obj_present[i][2]+27){
				if(obj_present[i][4]==0)
					power++;
				else if(type==obj_present[i][4])
					power++;
				else if(type!=obj_present[i][4]){
					type=obj_present[i][4];
					if(type==1)
						wait_fire_max=25;
					else if (type == 2)
						wait_fire_max=2;
					else if (type == 3)
						wait_fire_max=30;
				}
				current_score+=50;
				oslPlaySound(CI_sounds[4],4);
				obj_present[i][0]=0;
			}
		}
	}
}
void update_food()
{
	for(int i=1;i<=20;i++){
		if(obj_food[i][0]==2){
			sprites[int (obj_food[i][4])+6]->angle=obj_food[i][5];
			oslDrawImageXY(sprites[int (obj_food[i][4])+6],obj_food[i][1],obj_food[i][2]);
			obj_food[i][2]+=obj_food[i][3];
			obj_food[i][5]+=fabs(obj_food[i][3])*obj_food[i][6];
			if(obj_food[i][6]>0)
				obj_food[i][1]+=fabs(obj_food[i][3]);
			else if(obj_food[i][6]<0) 
				obj_food[i][1]-=fabs(obj_food[i][3]);
			if(obj_food[i][1]<0 || obj_food[i][1]>480)
				obj_food[i][6]*=-1;
			if(obj_food[i][3]<0.1 && obj_food[i][3]>-0.1 && obj_food[i][2]>=260){
					obj_food[i][0]=1;
					obj_food[i][6]=300;
			}
			obj_food[i][3]+=0.0125;
			if(obj_food[i][3]<0)    
				obj_food[i][3]+=0.0125;
			if(obj_food[i][2]>270){
				obj_food[i][3]=obj_food[i][3]/1.5*(-1);
				obj_food[i][2]=270;
			}
			if(ship->x+ship->stretchX>obj_food[i][1]-5 && ship->x<obj_food[i][1]+5 && ship->y+ship->stretchY>obj_food[i][2]-4 && ship->y<obj_food[i][2]+11){
				eats_food(int (obj_food[i][4]));
				obj_food[i][0]=0;
			}
		}
		else if(obj_food[i][0]==1){
			sprites[int (obj_food[i][4])+6]->angle=obj_food[i][5];
			oslDrawImageXY(sprites[int (obj_food[i][4])+6],obj_food[i][1],obj_food[i][2]);
			if(obj_food[i][6]!=0)
				obj_food[i][6]--;
			else
				obj_food[i][0]=0;
		}
	}
}
void update_bullets()
{
	for(int i=1;i<=50;i++)
		if(obj_bullets[i][0]>=1){
			oslDrawImageXY(bullets[int (obj_bullets[i][5])],obj_bullets[i][1],obj_bullets[i][2]);
			for(int o=1;o<=2;o++)
				if(obj_boss[o][0]==1	&& obj_bullets[i][1]+bullets[int(obj_bullets[i][5])]->stretchX>obj_boss[o][1]-21  && obj_bullets[i][1]<obj_boss[o][1]+21	  && obj_bullets[i][2]+bullets[int(obj_bullets[i][5])]->stretchY>obj_boss[o][2]-18	&& obj_bullets[i][2]<obj_boss[o][2]+29){
					if(obj_bullets[i][7]>0 && obj_bullets[i][8]!=o-10){
						obj_bullets[i][7]--;
						obj_bullets[i][8]=o-10;
						if(obj_bullets[i][7]==0)
							obj_bullets[i][0]=0;
						obj_boss[o][6]-=obj_bullets[i][6];
						if(type!=2)
							oslPlaySound(CI_sounds[6],5);
					}
				}
			for(int o=1;o<=40;o++)
				if(obj_chickens[o][0]==1 && obj_bullets[i][1]+bullets[int(obj_bullets[i][5])]->stretchX>obj_chickens[o][1] && obj_bullets[i][1]<obj_chickens[o][1]+50 && obj_bullets[i][2]+bullets[int(obj_bullets[i][5])]->stretchY>obj_chickens[o][2] && obj_bullets[i][2]<obj_chickens[o][2]+40){
					if(obj_bullets[i][7]>0 && obj_bullets[i][8]!=o){
						obj_bullets[i][7]--;
						obj_bullets[i][8]=o;
						if(obj_bullets[i][7]==0)
							obj_bullets[i][0]=0;
						obj_chickens[o][6]-=obj_bullets[i][6];
					}
				}
			obj_bullets[i][1]+=obj_bullets[i][3];
			obj_bullets[i][2]+=obj_bullets[i][4];
			if(obj_bullets[i][1]<-50 || obj_bullets[i][1]>500 || obj_bullets[i][2]<-50 || obj_bullets[i][2]>300)
				obj_bullets[i][0]=0;
		}
}
void update_chickens()
{
	for(int i=1;i<=40;i++)
		if(obj_chickens[i][0]==1){
			if(obj_chickens[i][6]<=0){
				obj_chickens[i][0]=0;
				chickens_on_level--;
				if(rand()%20==0)
					create_present(obj_chickens[i][1]+8.5,obj_chickens[i][2]+6.5,(rand()%3+3)/2,rand()%4);
				if(obj_chickens[i][5]<9){
					if(rand()%2==0)
						drop_food(obj_chickens[i][1],obj_chickens[i][2]);
					oslPlaySound(CI_sounds[1],2);
				}else
					oslPlaySound(CI_sounds[8],5);
				if(combo_time>0 && CI_bomb[0]==0){
					combo_multi++;
					combo_time=200;
				}
				else
					combo_time=200;
				current_score+=combo_multi*100;
				create_effects(7,obj_chickens[i][1]+20,obj_chickens[i][2]+15,1,32,0,0);
				continue;
			}
			if(ship->x+ship->stretchX>obj_chickens[i][1]+13 && ship->x<obj_chickens[i][1]+34 && ship->y+ship->stretchY>obj_chickens[i][2]+13 && ship->y<obj_chickens[i][2]+30 && respawn_invin==0){
				died();
				obj_chickens[i][0]=0;
				chickens_on_level--;
			}
			if(obj_chickens[i][8]==43){
				if(obj_chickens[i][5]==10)
					obj_chickens[i][5]=9;
				obj_chickens[i][8]=0;
			}
			if(obj_chickens[i][5]==9 && obj_chickens[i][8]/4>7)
				obj_chickens[i][5]=10;
			if(obj_chickens[i][5]<9 && rand()%700==0)
				create_eggs(obj_chickens[i][1]+8.5,obj_chickens[i][2]+6.5,(rand()%3+3)/2);
			if(obj_chickens[i][8]/4>6)
				oslSetImageTileSize(CI_chickens,50*(11-int(obj_chickens[i][8]/4)),40*(obj_chickens[i][5]-1),50,40);
			else
				oslSetImageTileSize(CI_chickens,50*int(obj_chickens[i][8]/4),40*(obj_chickens[i][5]-1),50,40);
			oslDrawImageXY(CI_chickens,obj_chickens[i][1],obj_chickens[i][2]);
			obj_chickens[i][8]++;
		}
}
void update_boss()
{
	for(int i=1;i<=2;i++)
		if(obj_boss[i][0]==1){
			if(obj_boss[i][6]<=0){
				obj_boss[i][0]=0;
				chickens_on_level--;
				create_present(obj_boss[i][1],obj_boss[i][2],(rand()%3+3)/2,rand()%4);
				for(int o=1;o<=5;o++)
					drop_food(obj_boss[i][1],obj_boss[i][2]);
				if(combo_time>0 && CI_bomb[0]==0){
					combo_multi++;
					combo_time=100;
				}
				else{
					combo_time=100;
					combo_multi=1;
				}
				current_score+=combo_multi*500;
				oslPlaySound(CI_sounds[7],5);
				create_effects(7,obj_boss[i][1]-12,obj_boss[i][2]-22,rand()%2+1,32,0,0);
				continue;
			}
			if(ship->x+ship->stretchX>obj_boss[i][1]-21 && ship->x<obj_boss[i][1]+21 && ship->y+ship->stretchY>obj_boss[i][2]-18 && ship->y<obj_boss[i][2]+29 && respawn_invin==0){
				died();
			}
			if(obj_boss[i][8]==79){
				obj_boss[i][8]=0;
			}
			if(rand()%80==0)
				create_eggs(obj_boss[i][1],obj_boss[i][2],(rand()%3+3)/2);
			if(obj_boss[i][8]>39)
				oslSetImageTileSize(CI_boss,(7-int(obj_boss[i][8]/10))*104,(obj_boss[i][5]-1)*83,104,83);
			else
				oslSetImageTileSize(CI_boss,   int(obj_boss[i][8]/10 )*104,(obj_boss[i][5]-1)*83,104,83);
			oslDrawImageXY(CI_boss,obj_boss[i][1],obj_boss[i][2]);
			obj_boss[i][8]++;
		}
}
void update_efects()
{
	int update;
	for(int i=1;i<=20;i++)
		if(obj_effects[i][0]==1){
			oslSetImageTileSize(CI_effects,0,0,32,32);
			obj_effects[i][7] += 1;
			CI_effects->stretchX=obj_effects[i][3]-obj_effects[i][7];
			CI_effects->stretchY=obj_effects[i][3]-obj_effects[i][7];
			if (obj_effects[i][7] > obj_effects[i][3])
				obj_effects[i][0]=0;
			obj_effects[i][1] +=obj_effects[i][5];
			obj_effects[i][2] +=obj_effects[i][6];
			update=255-255*(obj_effects[i][7]/obj_effects[i][3]);
			if(update < 0)
				update = 0;
			if(update > 255)
				update = 255;
			oslSetAlpha(OSL_FX_ALPHA,update);
			oslDrawImageXY(CI_effects,obj_effects[i][1],obj_effects[i][2]);
			oslSetAlpha(OSL_FX_RGBA,update);
		}
}
void eats_food (int ftype)
{
	switch(ftype){
		case 3:
			ftype=4;
			break;
		case 4:
			ftype=5;
			break;
		case 5:
			ftype=10;
			break;
		case 6:
			ftype=15;
			break;
		case 7:
			ftype=20;
			break;
		default:
			break;
		}
	eat_food+=ftype;
	current_score+=ftype*50;
	if(eat_food>=50){
		eat_food-=50;
		ammo_bomb++;
		oslPlaySound(CI_sounds[4],4);
		current_score+=5000;
	}else
		oslPlaySound(CI_sounds[5],4);
}
void drop_food (int LocX,int LocY)
{

	int food_type=1;
	if(rand()%5==0){	food_type++;
		if(rand()%5==0){	food_type++;
			if(rand()%5==0){	food_type++;
				if(rand()%5==0){	food_type++;
					if(rand()%5==0){	food_type++;
						if(rand()%5==0)		food_type++;
					}
				}
			}
		}
	}
	create_food(LocX+25,LocY+20,(rand()%3+2)/2,food_type,(rand()%18-9)*5);
}
void shoot_bomb()
{

	if(ammo_bomb>0 && CI_bomb[0]==0)
	{
		//draw able or not
		CI_bomb[0]=1;

		//point of origin
		CI_bomb[1]=ship->x+43/2; 
		CI_bomb[2]=ship->y+49/2;

		//set the speed
		CI_bomb[3]=rand()%6-3;
		if(CI_bomb[3]==0)
			CI_bomb[3]=4;
		CI_bomb[4]=150;
		ammo_bomb--;
	}
}
void shoot_bullet(){
	if (wait_fire <= 0 ){
		wait_fire = wait_fire_max;
		if (type == 1){
			oslPlaySound(CI_sounds[0],1);
			ship->y+=5;
			if (power == 1)
				create_bullet(18,0,0,-5,0,1,1);
			else if (power == 2){
				create_bullet(10,0,0,-5,0,1,1);
				create_bullet(25,0,0,-5,0,1,1);
			}else if (power == 3){
				create_bullet(10,  5,0,-5,0,1,1);
				create_bullet(17.5,0,0,-5,0,1,1);
				create_bullet(25,  5,0,-5,0,1,1);
			}else if (power == 4) {
				create_bullet(10, 20,-1,-5,0,1,1);
				create_bullet(17.5,5, 0,-5,0,1,1);
				create_bullet(25, 20, 1,-5,0,1,1);
			}else if (power == 5) {
				create_bullet(7, 20,0,-5,0,1,1);			
				create_bullet(10, 5,0,-5,0,1,1);
				create_bullet(27,20,0,-5,0,1,1);
				create_bullet(25, 5,0,-5,0,1,1);
			}else if (power == 6) {
				create_bullet(7,   20,0,-5,0,1,1);
				create_bullet(10,   5,0,-5,0,1,1);
				create_bullet(17.5,-5,0,-5,0,1,1);
				create_bullet(27,  20,0,-5,0,1,1);
				create_bullet(25,   5,0,-5,0,1,1);
			}else if (power == 7) {
				create_bullet(7,   20,-0.5,-5,0,1,1);
				create_bullet(10,   5,-0.5,-5,0,1,1);
				create_bullet(17.5,-5,   0,-5,0,1,1);
				create_bullet(27,  20, 0.5,-5,0,1,1);
				create_bullet(25,   5, 0.5,-5,0,1,1);
			}else if (power == 8){
				create_bullet(7, 20,-1,-5,0,1,1);
				create_bullet(10, 5,-1,-5,0,1,1);
				create_bullet(10, 0, 0,-5,0,1,1);
				create_bullet(25, 0, 0,-5,0,1,1);
				create_bullet(27,20, 1,-5,0,1,1);
				create_bullet(25, 5, 1,-5,0,1,1);
			}else if (power == 9){
				create_bullet(7,   20,-1,-5,0,2,1);
				create_bullet(10,   5,-1,-5,0,2,1);
				create_bullet(10,   5, 0,-5,0,2,1);
				create_bullet(17.5,-5, 0,-5,0,2,1);
				create_bullet(25,   5, 0,-5,0,2,1);
				create_bullet(27,  20, 1,-5,0,2,1);
				create_bullet(25,   5, 1,-5,0,2,1);
			}else if (power >= 10 && power < 20){
				create_bullet(7,   20,-1,-5,0,3,1);
				create_bullet(7,   20, 0,-5,0,3,1);
				create_bullet(10,   5,-1,-5,0,3,1);
				create_bullet(10,   5, 0,-5,0,3,1);
				create_bullet(17.5,-5, 0,-5,0,3,1);			
				create_bullet(27,  20, 1,-5,0,3,1);
				create_bullet(25,   5, 1,-5,0,3,1);
				create_bullet(27,  20, 0,-5,0,3,1);
				create_bullet(25,   5, 0,-5,0,3,1);
			}else if (power >= 20) {
				create_bullet(7,	20,  -2,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(7,	20,  -1,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(10,	 5,  -2,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(10,	 5,  -1,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(10,	 5,-0.5,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(17.5,	-5,   0,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(25,	 5, 0.5,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(27,	20,   2,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(25,	 5,   2,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(27,	20,   1,  -5, 0, 5+(power-20)*0.5, 1);
				create_bullet(25,	 5,   1,  -5, 0, 5+(power-20)*0.5, 1);
			}
		}
		if(type == 2){
			//oslPlaySound(CI_sounds[9],1);
			ship->y+=3;
			if (power == 1)
				create_bullet(19.5, -5,   0, -15, 1, 0.0625, 1);
			else if (power == 2){
				create_bullet(17.5, -5,   0, -15, 1, 0.0625, 1);
				create_bullet(21.5, -5,   0, -15, 1, 0.0625, 1);
			}else if (power == 3){
				create_bullet(15.5, -5,   0, -15, 1, 0.0625, 1);
				create_bullet(19.5, -5,   0, -15, 1, 0.0625, 1);
				create_bullet(23.5, -5,   0, -15, 1, 0.0625, 1);
			}else if (power == 4) {
				create_bullet(15.5, -5,   0, -15, 2,   0.25, 1);
			}else if (power == 5) {
				create_bullet(11.5, -5,   0, -15, 1, 0.0625, 1);
				create_bullet(15.5, -5,   0, -15, 2,   0.25, 1);
				create_bullet(27.5, -5,   0, -15, 1, 0.0625, 1);
			}else if (power == 6) {
				create_bullet(10.5, -5,   0, -15, 2,   0.25, 1);
				create_bullet(22.5, -5,   0, -15, 2,   0.25, 1);
			}else if (power == 7) {
				create_bullet(7.5,  -5,   0, -15, 2,   0.25, 1);
				create_bullet(19.5, -5,   0, -15, 1, 0.0625, 1);
				create_bullet(23.5, -5,   0, -15, 2,   0.25, 1);
			}else if (power == 8){
				create_bullet(3.5,-5,0,-15,1,0.0625,1);
				create_bullet(7.5,-5,0,-15,2,0.25,1);
				create_bullet(19.5,-5,0,-15,1,0.0625,1);
				create_bullet(23.5,-5,0,-15,2,0.25,1);
				create_bullet(35.5,-5,0,-15,1,0.0625,1);
			}else if (power == 9){
				create_bullet(3.5,-5,0,-15,2,0.25,1);
				create_bullet(15.5,-5,0,-15,2,0.25,1);
				create_bullet(27.5,-5,0,-15,2,0.25,1);
			}else if (power >= 10 && power < 20)
				create_bullet(  14.5, -5, 0,-15, 3,  1, 1);
			else if (power >=20) {
				create_bullet(   7.5, -5, 0,-15, 3,  1.5 + (power-20)*0.0625, 1);
				create_bullet(  21.5, -5, 0,-15, 3,  1.5 + (power-20)*0.0625, 1);
			}
		}
		if(type == 3){
			oslPlaySound(CI_sounds[0],1);//10
			ship->y+=5;
			if(power==1)
				create_bullet(   15, -5, 0, -4, 4, 0.5, 2);
			else if(power==2){
				create_bullet(    8, -5, 0, -4, 4, 0.5, 2);
				create_bullet( 21.5, -5, 0, -4, 4, 0.5, 2);
			}else if(power==3){
				create_bullet( 1.25, -5, 0, -4, 4, 0.5, 2);
				create_bullet(14.75, -5, 0, -4, 4, 0.5, 2);
				create_bullet(28.25, -5, 0, -4, 4, 0.5, 2);
			}else if(power==4){
				create_bullet( 1.25, -5,-1, -4, 4, 0.5, 2);
				create_bullet(14.75, -5, 0, -4, 4, 0.5, 2);
				create_bullet(28.25, -5, 1, -4, 4, 0.5, 2);
			}else if(power==5){
				create_bullet( 1.25, -5,-2, -4, 4, 0.5, 2);
				create_bullet(14.75, -5,-1, -4, 4, 0.5, 2);
				create_bullet(14.75, -5, 1, -4, 4, 0.5, 2);
				create_bullet(28.25, -5, 2, -4, 4, 0.5, 2);
			}else if(power==6){
				create_bullet( 1.25, -5,-2, -4, 4, 0.5, 2);
				create_bullet(14.75, -5,-1, -4, 4, 0.5, 2);
				create_bullet(14.75, -5, 0, -4, 4, 0.5, 2);
				create_bullet(14.75, -5, 1, -4, 4, 0.5, 2);
				create_bullet(28.25, -5, 2, -4, 4, 0.5, 2);
			}else if(power==7){
				create_bullet( 1.25, -5,-2, -4, 4, 0.5, 2);
				create_bullet(    9, -5, 0, -4, 5,   1, 3);
				create_bullet(28.25, -5, 2, -4, 4, 0.5, 2);
			}else if(power==8){
				create_bullet( 1.25, -5,-2, -4, 4, 0.5, 2);
				create_bullet(    9, -5,-1, -4, 5,   1, 3);
				create_bullet(    9, -5, 1, -4, 5,   1, 3);
				create_bullet(28.25, -5, 2, -4, 4, 0.5, 2);
			}else if(power==9){
				create_bullet( 1.25, -5,-2, -4, 4, 0.5, 2);
				create_bullet(    9, -5,-1, -4, 5,   1, 3);
				create_bullet(    9, -5, 0, -4, 4, 0.5, 2);
				create_bullet(    9, -5, 1, -4, 5,   1, 3);
				create_bullet(28.25, -5, 2, -4, 4, 0.5, 2);
			}else if(power==9){
				create_bullet( 1.25, -5,-1, -4, 5,   1, 3);
				create_bullet(    9, -5,-1, -4, 5,   1, 3);
				create_bullet(    9, -5, 0, -4, 5,   1, 3);
				create_bullet(    9, -5, 1, -4, 5,   1, 3);
				create_bullet(28.25, -5, 1, -4, 5,   1, 3);
			}else if(power>=10 && power<20){
				create_bullet( 1.25, -5,-2, -4, 5,   1, 3);
				create_bullet(    9, -5,-1, -4, 5,   1, 3);
				create_bullet(    9, -5, 0, -4, 6,   2, 4);
				create_bullet(    9, -5, 1, -4, 5,   1, 3);
				create_bullet(28.25, -5, 2, -4, 5,   1, 3);
			}else if(power>=20){
				create_bullet( 1.25, -5,-3, -4, 5, 1+(power-20)*0.5, 3);
				create_bullet(    9, -5,-2, -4, 5, 1+(power-20)*0.5, 3);
				create_bullet(    9, -5,-1, -4, 6, 2+(power-20)*0.5, 4);
				create_bullet(    9, -5, 0, -4, 6, 2+(power-20)*0.5, 4);
				create_bullet(    9, -5, 1, -4, 6, 2+(power-20)*0.5, 4);
				create_bullet(    9, -5, 2, -4, 5, 1+(power-20)*0.5, 3);
				create_bullet(28.25, -5, 3, -4, 5, 1+(power-20)*0.5, 3);
			}
		}
	}
}
void set_levels ()
{
    if(space_warp==1 && chickens_on_level==0 && level_cooldown_timer>0){
		level_cooldown_timer--;
		int next_level=nr_level%10+1;
		if(nr_level/*-difficulty*10*/<10){
			oslPrintf_xy(200,110,"Level %d",(difficulty-1)*10+next_level);
			switch(next_level){
				case 1:		oslPrintf_xy(200,135,"Wake up!"); break;
				case 2:		oslPrintf_xy(180,135,"Need some coffe?"); break;
				case 3:		oslPrintf_xy(160,135,"Warning, astroids incoming!"); break;
				case 4:		oslPrintf_xy(200,135,"Chicken Storm"); break;
				case 5:		oslPrintf_xy(200,135,"Get ready for war!"); break;
				case 6:		oslPrintf_xy(170,135,"High speed astroids!"); break;
				case 7:		oslPrintf_xy(170,135,"Be quick or be dead!"); break;
				case 8:		oslPrintf_xy(150,135,"Warning, astroids incoming! again"); break;
				case 9:		oslPrintf_xy(150,135,"Wake up! part 3"); break;
				case 10:	oslPrintf_xy(170,135,"Show em who`s boss!"); break;
				case 11:	oslPrintf_xy(200,135,"Wake up!"); break;
				case 12:	oslPrintf_xy(180,135,"Need some coffe?"); break;
				case 13:	oslPrintf_xy(160,135,"Warning, astroids incoming!"); break;
				//case 4:	oslPrintf_xy(200,135,"Terminator"); break;
				case 14:	oslPrintf_xy(200,135,"Chicken Storm"); break;
				case 15:	oslPrintf_xy(200,135,"Get ready for war!"); break;
				case 16:	oslPrintf_xy(170,135,"High speed astroids!"); break;
				case 17:	oslPrintf_xy(170,135,"Be quick or be dead!"); break;
				case 18:	oslPrintf_xy(150,135,"Warning, astroids incoming! again"); break;
				case 19:	oslPrintf_xy(150,135,"Wake up! part 3"); break;
				case 20:	oslPrintf_xy(170,135,"Show em who`s boss!"); break;
			}
		}
	}
	if(level_cooldown_timer<=0){
		level_cooldown_timer=100;
		nr_level++;
		if (nr_level == 13){
			nr_level = 0; //difficulty*10+1;
			difficulty++;
		}
		if(nr_level-difficulty*10<=0){
			remove_chickens();
			/*if (CI_level[nr_level] == 1){
				remove_chickens();
				for (int i = 1;i<=8;i++){
					for (int o = 1; o<=3;o++){
						create_chicken(0,(o+(i-1)*3)*(-45),1,1,0,difficulty);
						obj_chickens[(o+(i-1)*3)][4]=i*50;
						obj_chickens[(o+(i-1)*3)][7]=(o-1)*45;
						chickens_on_level = chickens_on_level + 1;
					}
				}
			}else*/ if (nr_level == 1 || nr_level == 2){
				for (int i = 1;i<=8;i++){
					for (int o = 1; o<=4;o++){
						if(nr_level==1)		create_chicken(i*50-480,(o-1)*45,1,1,0,difficulty);
						else if(nr_level==2)	create_chicken(i*50+480,(o-1)*45,1,1,0,difficulty);
						chickens_on_level = chickens_on_level + 1;
					}
				}
			}else if (nr_level ==3) {
				for(int i = 1;i<=5+difficulty*2;i++){
					create_chicken(rand()%10*40 - 500,rand()%10*20-150,9,rand()%6*4,(rand()%40*10/100)+2,difficulty+rand()%5);
					chickens_on_level = chickens_on_level + 1;
				 }
			}else if (nr_level == 4) {
				for (int i = 1;i<=5+difficulty*2;i++) {
					create_chicken(rand()%11*40,rand()%15*20*(-1)-100,1,rand()%10*4,0, difficulty);
					chickens_on_level = chickens_on_level + 1;
				}
			}else if (nr_level == 5){
				for(int i = 1;i<=5+difficulty*2;i++){
					int tmp = rand()%2;
					if (tmp == 1 ) create_chicken(-50,rand()%12*10,1,rand()%10*4,0,difficulty); else create_chicken(520,rand()%12*10,1,rand()%10*4,0,difficulty);
					tmp = rand()%2;
					if (tmp == 1 ) obj_chickens[i][3]=((rand()%10*4/10)+1); else obj_chickens[i][3]=(((rand()%10*4/10)*-1)-1);
					tmp = rand()%2;
					if (tmp == 1 ) obj_chickens[i][4]=((rand()%10*4/10)+1); else obj_chickens[i][4]=(((rand()%10*4/10)*-1)-1);
					chickens_on_level = chickens_on_level + 1;
				}
			}else if (nr_level == 6) {
				for(int i = 1;i<=5+difficulty*2;i++){
					create_chicken(rand()%44*10,rand()%20*100-2024,9,rand()%6*4,rand()%10*4/10+3, difficulty+1);
					chickens_on_level = chickens_on_level + 1;
				}
			}else if (nr_level == 7) {
				for (int i = 1;i<=(difficulty * 2) + 5;i++) {
					create_chicken(rand()%22*20,rand()%10*10-150,1,rand()%10*4,(rand()%20*10/50)+2, difficulty);
					chickens_on_level = chickens_on_level + 1;
				}
			}else if (nr_level == 8) {
				for (int i = 1;i<=5+difficulty*2;i++){
					create_chicken(rand()%11*10,rand()%20*10-200,9,rand()%6*4,((rand()%50)/10)-3, difficulty+1);
					obj_chickens[i][4]=((rand()%40)/10)+1;
					chickens_on_level = chickens_on_level + 1;
				}
			}else if (nr_level == 9) {
				obj_chickens[0][1]=5+difficulty*2;
				create_chicken(rand()%44*(-10),rand()%25*2-100,1,rand()%10*4,0, difficulty);
				chickens_on_level = chickens_on_level + 1;
			}else if (nr_level == 10) {
				create_boss(rand()%44*10,rand()%25*2-100,1,rand()%4,difficulty, difficulty*25);
				obj_boss[1][4]=difficulty;
				chickens_on_level = chickens_on_level + 1;
			}
		}
	}
}
void move_chickens ()
{
	if(nr_level/*-difficulty*10*/<=10){
		/*if (CI_level[nr_level] == 1){
			if(obj_chickens[i][0]==1){
					if (obj_chickens[i][1] < 0)   chicken_move_direction = 2;
					if (obj_chickens[i][1] > 430) chicken_move_direction = 1;
				}
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					if(obj_chickens[i][1]<obj_chickens[i][4] &&)
						obj_chickens[i][1]+=obj_chickens[i][3];
					else {
				}
			}*/
		if (nr_level == -1){
			if(space_warp>1)
				space_warp--;
			else
				level_cooldown_timer=0;
		}else if (nr_level == 1 || nr_level == 2 ){
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					if (obj_chickens[i][1] < 0){   chicken_move_direction = 2;	break;}
					if (obj_chickens[i][1] > 430){ chicken_move_direction = 1;	break;}
				}
			}
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					if (chicken_move_direction == 2) obj_chickens[i][1] +=  (1 + difficulty/4);
					if (chicken_move_direction == 1) obj_chickens[i][1] -=  (1 + difficulty/4);	
				}
			}
		}else if (nr_level == 3){
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					obj_chickens[i][1] += obj_chickens[i][3];
					obj_chickens[i][2] += obj_chickens[i][3] * 0.25;
					/*if(rand()%10 == 1)
						create_effects(1,obj_chickens[i][1],obj_chickens[i][2],0,14,obj_chickens[i][3]*(-1),obj_chickens[i][3]*(-1)*0.25);*/
					if(obj_chickens[i][1]>500 || obj_chickens[i][2]>300){
						obj_chickens[i][0]=0;
						chickens_on_level--;
					}
				}
			}
		}else if (nr_level == 4){
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					obj_chickens[i][2] += (difficulty/4) + 1;
					if (obj_chickens[i][2] > 272)
						obj_chickens[i][2]=-272;
				}
			}
		}else if (nr_level == 5) {
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					obj_chickens[i][1] += obj_chickens[i][3];
					obj_chickens[i][2] += obj_chickens[i][4];
					if (obj_chickens[i][1] < 3	 && obj_chickens[i][3] < 0) obj_chickens[i][3] = obj_chickens[i][3] * -1;
					if (obj_chickens[i][1] > 440 && obj_chickens[i][3] > 0) obj_chickens[i][3] = obj_chickens[i][3] * -1;
					if (obj_chickens[i][2] < 3   && obj_chickens[i][4] < 0) obj_chickens[i][4] = obj_chickens[i][4] * -1;
					if (obj_chickens[i][2] > 160 && obj_chickens[i][4] > 0) obj_chickens[i][4] = obj_chickens[i][4] * -1;
				}
			}
		}else if (nr_level == 6){
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					obj_chickens[i][2] += obj_chickens[i][3];
					if(obj_chickens[i][2]>300){
						obj_chickens[i][0]=0;
						chickens_on_level--;
					}
					/*if(rand()%10 == 1)
						create_effects(1,obj_chickens[i][1],obj_chickens[i][2],0,14,39039,obj_chickens[i][3]*(-1));*/
				}
			}
		}else if (nr_level == 7) {
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					obj_chickens[i][1] += obj_chickens[i][3];
					obj_chickens[i][2] += 1;
					if (obj_chickens[i][1] <   3 && obj_chickens[i][3] < 0) obj_chickens[i][3] *= -1;
					if (obj_chickens[i][1] > 440 && obj_chickens[i][3] > 0) obj_chickens[i][3] *= -1;
					if(obj_chickens[i][2]>300){
						obj_chickens[i][0]=0;
						chickens_on_level--;
					}
				}
			}
		}else if (nr_level == 8) {
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					obj_chickens[i][1] += obj_chickens[i][3];
					obj_chickens[i][2] += obj_chickens[i][4];
					if(obj_chickens[i][2]>300 || obj_chickens[i][1]>500 || obj_chickens[i][1]<-20){
						obj_chickens[i][0]=0;
						chickens_on_level--;
					}
					/*if(rand()%10 == 1)
						create_effects(1,obj_chickens[i][1],obj_chickens[i][2],0,14,obj_chickens[i][3]*(-1),obj_chickens[i][4]*(-1));*/
				}
			}
		}else if (nr_level==9){
			for (int i=1;i<=40;i++) {
				if(obj_chickens[i][0]==1){
					int check=0;
					if(obj_chickens[i][2]+20+(difficulty/2)+1<obj_chickens[i][4]-2){
						obj_chickens[i][2]+=(difficulty/2)+1;		check=1;
					}else if(obj_chickens[i][2]+20-(difficulty/2)+1>obj_chickens[i][4]+2){
						obj_chickens[i][2]-=(difficulty/2)+1;		check=1;
					}
					if(obj_chickens[i][1]+25+(difficulty/4)+1<obj_chickens[i][3]-2){
						obj_chickens[i][1]+=(difficulty/4)+1;		check=1;
					}else if(obj_chickens[i][1]+25-(difficulty/4)+1>obj_chickens[i][3]+2){
						obj_chickens[i][1]-=(difficulty/4)+1;		check=1;
					}
					if(obj_chickens[i][7]==0){
						obj_chickens[i][7]=-1;
						obj_chickens[i][3]=ship->x+ship->stretchX/2;
						obj_chickens[i][4]=ship->y+ship->stretchY/2;
					}else if (obj_chickens[i][7]>0)
						obj_chickens[i][7]--;
					else if(check==0)
						obj_chickens[i][7]=rand()%10*10+50;
				}
			}
			if(chickens_on_level<5 && obj_chickens[0][1]>0){
				if(rand()%2==0)		create_chicken(rand()%44*(-10) ,rand()%25*2-100,1,rand()%10*4,0, difficulty);
				else 				create_chicken(rand()%44*10+480,rand()%25*2-100,1,rand()%10*4,0, difficulty);
				chickens_on_level = chickens_on_level + 1;
				obj_chickens[0][1]--;
			}
		}else if (nr_level == 10) {
			for (int i=1;i<=2;i++) {
				if(obj_boss[i][0]==1){
					obj_boss[i][1] += obj_boss[i][3];
					obj_boss[i][2] += obj_boss[i][4];
					if (obj_boss[i][1] < 3	 && obj_boss[i][3] < 0) obj_boss[i][3] = obj_boss[i][3] * -1;
					if (obj_boss[i][1] > 440 && obj_boss[i][3] > 0) obj_boss[i][3] = obj_boss[i][3] * -1;
					if (obj_boss[i][2] < 3   && obj_boss[i][4] < 0) obj_boss[i][4] = obj_boss[i][4] * -1;
					if (obj_boss[i][2] > 160 && obj_boss[i][4] > 0) obj_boss[i][4] = obj_boss[i][4] * -1;
				}
			}
		}
	}else if (nr_level == 11){
		if(space_warp<100)
			space_warp++;
		else
			level_cooldown_timer=0;
	}
	else if (nr_level == 12){/*difficulty*10*/
		if(space_warp>1)
			space_warp--;
		else
			level_cooldown_timer=0;
	}
}
void died ()
{
	lives--;
	respawn_invin=100;
	if(power>20)
		power-=5;
	else if(power>10)
		power-=3;
	else if(power>5)
		power-=2;
	else if(power>1)
		power--;
	oslPlaySound(CI_sounds[3],5);
}
void respawn()
{
  respawn_invin = respawn_invin - 1;
  if (respawn_invin > 50)
    ship->y=200 + ((respawn_invin - 50) * 2);
  else
	 ship->y=200;
}
void create_food(double foodX,double foodY,double speed,int ftype,double fangle)
{
	for(int i=1;i<=20;i++)
		if(obj_food[i][0]==0){
			obj_food[i][0]=2;
			obj_food[i][1]=foodX;
			obj_food[i][2]=foodY;
			obj_food[i][3]=speed;
			obj_food[i][4]=ftype;
			obj_food[i][5]=fangle;
			if(fangle>0)
				obj_food[i][6]=1;
			else if(fangle<0)
				obj_food[i][6]=-1;
			break;
		}
}
void create_present(double presentX,double presentY,double speed,int ptype)
{
	for(int i=1;i<=10;i++)
		if(obj_present[i][0]==0){
			obj_present[i][0]=1;
			obj_present[i][1]=presentX;
			obj_present[i][2]=presentY;
			obj_present[i][3]=speed;
			obj_present[i][4]=ptype;
			break;
		}
}
void create_eggs(double eggsX,double eggsY,double speed)
{
	for(int i=1;i<=40;i++)
		if(obj_eggs[i][0]==0){
			obj_eggs[i][0]=1;
			obj_eggs[i][1]=eggsX;
			obj_eggs[i][2]=eggsY;
			obj_eggs[i][3]=speed;
			break;
		}
}
void create_chicken(double chickenX,double chickenY,int ctype,int frame,int speed,int chealth)
{
	for(int i=1;i<=40;i++)
		if(obj_chickens[i][0]==0){
			obj_chickens[i][0]=1;
			obj_chickens[i][1]=chickenX;
			obj_chickens[i][2]=chickenY;
			obj_chickens[i][3]=speed;
			obj_chickens[i][4]=0;
			obj_chickens[i][5]=ctype;
			obj_chickens[i][6]=chealth;
			obj_chickens[i][7]=0;
			obj_chickens[i][8]=frame;
			break;
		}
}
void create_boss(double bossX,double bossY,int bosstype,int frame,int speed,int bhealth)
{
	for(int i=1;i<=2;i++)
		if(obj_boss[i][0]==0){
			obj_boss[i][0]=1;
			obj_boss[i][1]=bossX;
			obj_boss[i][2]=bossY;
			obj_boss[i][3]=speed;
			obj_boss[i][4]=0;
			obj_boss[i][5]=bosstype;
			obj_boss[i][6]=bhealth;
			obj_boss[i][7]=0;
			obj_boss[i][8]=frame;
			break;
		}
}
void create_bullet(double bulletX,double bulletY,double speedX,double speedY,int btype,double dmg,int blife)
{
	for(int i=1;i<=50;i++)
		if(obj_bullets[i][0]==0){
			obj_bullets[i][0]=1;
			obj_bullets[i][1]=ship->x+bulletX;
			obj_bullets[i][2]=ship->y+bulletY;
			obj_bullets[i][3]=speedX;
			obj_bullets[i][4]=speedY;
			obj_bullets[i][5]=btype;
			obj_bullets[i][6]=dmg;
			obj_bullets[i][7]=blife;
			obj_bullets[i][8]=0;
			break;
		}
}
void create_effects(int number,int effectX,int effectY,int effect_type,int effect_size,int eff_dirX,int eff_dirY)
{
	for(int i=1;i<=20;i++)
		if(obj_effects[i][0]==0){
			obj_effects[i][0]=1;
			obj_effects[i][1]=effectX;
			obj_effects[i][2]=effectY;
			obj_effects[i][3]=effect_size;
			obj_effects[i][4]=effect_type;
			do{
				obj_effects[i][5]=(eff_dirX)!= (0)?(eff_dirX):(rand()%4-2);
			}while(!obj_effects[i][5]);
			do{
				obj_effects[i][6]=(eff_dirY)!= (0)?(eff_dirY):(rand()%5-2);
			}while(!obj_effects[i][6]);
			if(obj_effects[i][5]==39039)
				obj_effects[i][5]=0;
			if(obj_effects[i][6]==39039)
				obj_effects[i][6]=0;
			obj_effects[i][7]=0;
			number--;
			if(number==0)
				break;
		}
}
void kill_chickens()
{
	for(int i=0;i<=50;i++){
		if(obj_chickens[i][1]>=-20 && obj_chickens[i][1]<=500 && obj_chickens[i][2]>=-20 && obj_chickens[i][2]<=290)
			obj_chickens[i][6]=-10;
	}
}
void remove_chickens()
{
	for(int i=0;i<=50;i++){
		for(int j=0;j<=8;j++)
			obj_chickens[i][j]=0;
	}
}
void remove_eggs()
{
	for(int i=0;i<=40;i++){
		for(int j=0;j<=3;j++)
			obj_eggs[i][j]=0;
	}
}
