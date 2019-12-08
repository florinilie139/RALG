/*
Author: (|EcLiPsE|)
Date: 11/2/2011
REremake Date: 22/11/2011
*/

int debugON=0;

#include "lib.h"
#include "icon.h"

PSP_MODULE_INFO("RALG", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

FILE* debugh;
OSL_IMAGE *select[5],*button[4],*title[20],*graphics[30],*achievements[20],*actitle[20],*mouse,*GG[3];

FILE* user;
OSL_FONT* font;
OSL_FONT* big_font;

time_t start,end;
int atime;
int ac[11];
int tlvl=10;
int tilvl=3;
int rndlvl;
int lvl[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,20};
int hi[11];
int analog=126;
int touch;
int clvl=1;
int done;
int frame=0;
int glvl;
int time_elapsed;
int seconds;
int tl;
int rl;
int plus;
int lose;
int move_enable;
int draw_mouse;
int loses;
int move;
int lmove;
int maxobj=0;
char state='m';

#include "object.h"
#include "initial.h"
#include "functions.h"
#include "saveload.h"
#include "street.cpp"
#include "ci.cpp"
#include "level.cpp"


int main ()
{
	initOSLib();
	LoadImages();
	debugh=fopen("debug.txt","w");
	obj[0].image=graphics[0];	obj[0].image->x=203;	obj[0].image->y=227;	obj[0].fx1=277;	obj[0].fy1=45;	obj[0].frame=0; obj[0].aux=1;
	while (!osl_pad.pressed.start && !osl_quit)
	{
		oslStartDrawing();
		obj[0].frame+=obj[0].aux;
		if(obj[0].frame==29 || obj[0].frame==-1)
			obj[0].aux*=-1;
		oslSetImageTileSize(obj[0].image,0,(obj[0].frame/3)*45,obj[0].fx1,obj[0].fy1);
		oslDrawImage(title[0]);
		oslDrawImage(obj[0].image);
		oslEndDrawing();
		oslSyncFrame();
		oslReadKeys();
	}
	load();
	memset(&obj[0], 0, sizeof(obj[0]));
	obj[0].frame=0;
	while (osl_quit!=1){
		oslStartDrawing();
		oslReadKeys();
		if(state=='m'){
			if(done==1){
				oslDrawImage(title[1]);
				oslDrawImage(select[frame]);
				if(osl_pad.pressed.down){
					if(frame==4)
						frame=0;
					else
						frame++;
				}else if(osl_pad.pressed.up){
					if(frame==0)
						frame=4;
					else
						frame--;
				}else if(osl_pad.pressed.cross){
					done=0;
					switch(frame){
						case 0:
							state='g';
							break;
						case 1:
							state='i';
							break;
						case 2:
							state='l';
							break;
						case 3:
							state='o';
							break;
						case 4:
							state='e';
							break;
					}
					frame=0;
				}
			}else{
				transition(title[1],rand()%5+1);
				fnc_menu();
				done=1;
			}
		}else if(state=='g'){
			if(done>=1){
				if(lose==0){
					if((clvl-1)/5<=glvl){
						if(osl_pad.pressed.start){
							erase();
							oslSetTextColor(black);
							state='m';
							lose=0;
							done=0;
							continue;
						}
						level();
					}else{
						oslDrawImage(GG[clvl/5]);
						if(osl_pad.pressed.circle || osl_pad.pressed.cross){
							glvl++;
							if(tlvl<glvl*5)
								tlvl=glvl*5;
							else if(tilvl<glvl && tlvl==10){
								tilvl++;
								fnc_achievements(glvl);
							}
						}
					}
				}else{
					oslDrawImage(title[7]);
					if(osl_pad.pressed.circle || osl_pad.pressed.cross){
						oslSetTextColor(black);
						erase();
						state='m';
						done=0;
						lose=0;
					}
				}
			}else{
				randlvl();
				clvl=1;
				glvl=0;
				done=1;
			}
		}else if(state=='n'){
			if(done==1)
				inflevel();
		}else if(state=='i'){
			if(done==3){
				oslDrawImage(title[8]);
				if(osl_pad.pressed.L)
					done=0;
				if(osl_pad.pressed.circle){
					state='m';
					done=0;
				}
			}else if(done==2){
				transition(title[8],rand()%5+1);
				done=3;
			}else if(done==1){
				oslDrawImage(title[3]);
				if(osl_pad.pressed.R)
					done=2;
				if(osl_pad.pressed.circle){
					state='m';
					done=0;
				}
			}else{
				transition(title[3],rand()%5+1);
				done=1;
			}
		}else if(state=='l'){
			if(done==1 || done==2){
				oslDrawImage(title[2]);
				oslDrawFillRect(17,46,19+(7*64),48+(64*3),black);
				oslPrintf_xy(10,11,"page: %d    press L or R to change the page",done);
				for (int x=0,y=0;y*7+x<21;x++)
				{
					if ((done==1 && (y*7+x)<=tlvl-1)||(done==2 && (y*7+x)<=tilvl-1))
						oslDrawFillRect(18+(x*64),48+(64*y),19+(x*64)+62,48+(64*y)+62,blue);
					else
						oslDrawFillRect(19+(x*64),48+(64*y),19+(x*64)+62,48+(64*y)+62,red);
					oslPrintf_xy(19+25+(x*64),70+(64*y),"%d",y*7+x+1);
					if(x==6){
						y++;
						x=-1;
					}
				}
				controls();
				if(osl_pad.pressed.cross)
				{
					for (int x=0,y=0;y*7+x<tlvl;x++)
					{
						if(mouse->x>=19+(x*64) && mouse->x<=19+(x+1)*64 &&  mouse->y>=48+(64*y) && mouse->y<=48+64+(64*y))
						{
							if(done==1){
								sort(lvl+1,lvl+15);
								state='g';
								glvl=3;
								clvl=y*7+x+1;
								done=1;
								frame=0;
								break;
							}
							if(done==2 && y*7+x+1<=tilvl){
								state='n';
								clvl=y*7+x+1;
								done=1;
								frame=0;
								break;
							}
						}
						if((x+1)%7==0){
							y++;
							x=0;
						}
					}
				}
				if(osl_pad.pressed.circle)
				{
					done=0;
					state='m';
				}
				if(osl_pad.pressed.R)
					done=2;
				if(osl_pad.pressed.L)
					done=1;
			}else{
				transition(title[2],rand()%5+1);
				done=1;
			}
		}else if(state=='o'){
			if(done>=1){
				oslSetFont(big_font);
				oslDrawImage(title[2]);
				oslPrintf_xy(75,74,Options[0]);
				oslPrintf_xy(200,74,RandOp[rndlvl]);
				oslPrintf_xy(75,94,Options[1],analog,osl_pad.analogX,osl_pad.analogY);
				oslPrintf_xy(75,114,Options[2]);
				oslPrintf_xy(75,134,Options[3]);
				oslPrintf_xy(75,154,Options[4]);
				oslPrintf_xy(75,174,Options[5]);
				oslSetTextColor(red);
				if(done==1){
					oslPrintf_xy(75,74,Options[0]);
					oslPrintf_xy(200,74,RandOp[rndlvl]);
					if(osl_pad.pressed.left)
					{
						if(rndlvl==0)
							rndlvl=2;
						else
							rndlvl--;
					}
					if(osl_pad.pressed.right){
						if(rndlvl==2)
							rndlvl=0;
						else
							rndlvl++;
					}
				}else if(done==2){
					oslPrintf_xy(75,94,Options[1],analog,osl_pad.analogX,osl_pad.analogY);
					if(osl_pad.pressed.left)
						if(analog!=0)
							analog-=3;
					if(osl_pad.pressed.right){
						if(analog!=126)
							analog+=3;
					}
				}else if(done==3){
					oslPrintf_xy(75,114,Options[2]);
					if(osl_pad.pressed.cross){
						state='a';
						done=0;
					}
				}else if(done==4){
					oslPrintf_xy(75,134,Options[3]);
					if(osl_pad.pressed.cross){
						state='s';
						done=0;
					}
				}else if(done==5){
					oslPrintf_xy(75,154,Options[4]);
					if(osl_pad.pressed.cross)
						save();
				}else if(done==6){
					oslPrintf_xy(75,174,Options[5]);
					if(osl_pad.pressed.cross){
						oslSetKeyAnalogToDPad(analog);
						done=0;
						state='m';
					}
				}
				if(osl_pad.pressed.up)
				{
					if(done==1)
						done=6;
					else
						done--;
				}
				if(osl_pad.pressed.down){
					if(done==6)
						done=1;
					else
						done++;
				}
				oslSetTextColor(black);
				oslSetFont(font);
			}else{
				transition(title[2],rand()%5+1);
				done=1;
			}
		}else if(state=='s'){
			if(done>=1){
				oslSetFont(big_font);
				oslDrawImage(title[2]);
				oslPrintf_xy(75,74,Stats[0],time_elapsed/3600,time_elapsed/60%60,time_elapsed%60);
				oslPrintf_xy(75,94,Stats[1],tlvl);
				oslPrintf_xy(75,114,Stats[2],tilvl);
				oslPrintf_xy(75,134,Stats[3],acu.type);
				oslPrintf_xy(75,154,Stats[4],lose);
				oslSetTextColor(red);
				oslPrintf_xy(75,194,Options[5]);
				oslSetTextColor(black);
				oslSetFont(font);
				if(osl_pad.pressed.circle || osl_pad.pressed.cross)
				{
					done=0;
					state='o';
					acu.aux=0;
				}
			}else{
				for(int i=1;i<10;i++)
					acu.type+=ac[i];
				transition(title[2],rand()%5+1);
				done=1;
			}
		}else if(state=='a'){
			if(done>=1){
				oslSetFont(big_font);
				oslDrawImage(title[2]);
				oslDrawImageXY(actitle[done], 176, 40);
				if(ac[done]==1)
					oslDrawImageXY(achievements[done], 176, 72);
				else
					oslDrawImageXY(achievements[0], 176, 72);
				oslPrintf_xy(10,72+128+32,AcDetail[done]);
				oslSetFont(font);
				if(osl_pad.pressed.left && done>1)
					done--;
				else if(osl_pad.pressed.right && done<10)
					done++;
				else if(osl_pad.pressed.circle)
				{
					done=0;
					state='o';
				}
			}else{
				transition(title[2],rand()%5+1);
				done=1;
			}
		}else if(state=='e'){
			if(done>=1){
				oslDrawImage(title[10]);
				done++;
				if(done==250)
					osl_quit=1;
			}else {
				transition(title[10],rand()%5+1);
				done=1;
			}
		}
		DrawAchievement();
		oslEndDrawing();
		oslSyncFrame();
		time (&end);
		seconds= difftime (end,start);
		time_elapsed+=seconds;
		if(ac[10]==0 && time_elapsed>7200)
			fnc_achievements(10);
		time (&start);
	}
	fclose(debugh);
	oslEndGfx();
	oslQuit();
	return 0;
}