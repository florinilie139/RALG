object obj[25],acu;

char ACUnlocked[2][30]={"Achievement","Unlocked"};
char RandOp[3][30]={"Disable","Mixing levels in 5 of 5","Enable"};
char AcDetail[11][80]={"","Finish the first 5 levels without a fail a second time","Finish the first 10 levels without a fail a second time","Lose 3 times at the same level","Lose 5 times continous","Find another way to finish level 5","Press the button until its 0","Reach round 40 at level 1 in the infinite mode","Reach 6000 score at level 2 in the infinite mode","Finish the game without failing a second time","Play the game for 2 hours"};
char Options[6][40]={"Random levels","Analog to pad Sensitivity: %d X:%d Y:%d","Achievements","Statistics","Save","Back"};
char Stats[6][40]={"Time played:%2d:%2d:%2d","Normal Levels Unlocked: %d","Infinite  Levels Unlocked: %d","Achievements Unlocked: %d","Time lose: %d"};
char LvL1Details[8][60]={"","Press the blue button to contiune","Press anywhere, but not the blue button, to contiune","Press anywhere, but not the green button, to contiune","Press the red button, to contiune","Press anywhere, but not the yellow button, to contiune","Quick press the green button, to contiune"};
char LvL2Details[3][60]={"","Press square on the duck to move it, do not hold","Move it to the square."};
char LvL3Details[3][30]={"","Catch the duck to continue.","Don't touch the bomb."};
char LvL4Details[4][40]={"","Move the happy faces to the square","And move the sad faces to the circle","Then press Continue."};
char LvL5Details[3][30]={"","Don't press the button","Quick! Don't press it!"};
char LvL6Details[40]={"Just kidding, press continue to move on"};
char LvL7Details[60]={"You are the frog, move to the other side, to the lake"};
char LvL8Details[40]={"It's EASY, Press the cas to continue."};
char LvL9Details[3][30]={"","Don't even think about it.","Go ahead ... quick!!"};
char LvL10Details[4][30]={"ENTER PASS","Look at the info!","It's refers to the altitude","ENTER"};


int initOSLib(){
    oslInit(0);
	oslInitGfx(OSL_PF_8888, 0);
	oslInitConsole();
    oslInitAudio();
    oslSetQuitOnLoadFailure(1);
	//oslSetQuitOnLoadFailureCallback(FailCallback);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
	srand((unsigned)time(0));
    return 0;
}
int LoadImages ()
{
	char trans[50];
	oslStartDrawing();
	big_font = oslLoadFontFile("comics 20.oft");
	font = oslLoadFontFile("comics.oft");
	oslSetFont(font);
	oslSetTextColor(blue);
	oslSetBkColor(RGBA(0, 0, 0, 0));
	oslPrintf_xy(208,86,"LOADING...");
	oslDrawHealthBar(120,106,240,60,10,100,2);
	for(int i=0;i<=4;i++){
		sprintf(trans,"graphics/select%d.png",i);
		select[i]=oslLoadImageFilePNG(trans, OSL_IN_RAM , OSL_PF_5551);
	}
	oslDrawHealthBar(120,106,240,60,20,100,2);
	for(int i=0;i<=3;i++){
		sprintf(trans,"graphics/button%d.png",i);
		button[i]=oslLoadImageFilePNG(trans, OSL_IN_RAM , OSL_PF_5551);
	}
	oslDrawHealthBar(120,106,240,60,30,100,2);
	for(int i=0;i<=10;i++)
	{
		sprintf(trans,"graphics/achievements/ac%d.png",i);
		achievements[i]=oslLoadImageFilePNG(trans, OSL_IN_RAM , OSL_PF_5551);
	}
	oslDrawHealthBar(120,106,240,60,40,100,2);
	for(int i=1;i<=10;i++)
	{
		sprintf(trans,"graphics/achievements/i%d.png",i);
		actitle[i]=oslLoadImageFilePNG(trans, OSL_IN_RAM , OSL_PF_5551);
	}
	oslDrawHealthBar(120,106,240,60,50,100,2);
	title[0]=oslLoadImageFilePNG("graphics/screen.png" , OSL_IN_RAM , OSL_PF_8888);
	title[1]=oslLoadImageFilePNG("graphics/menu.png" , OSL_IN_RAM , OSL_PF_8888);
	title[2]=oslLoadImageFilePNG("graphics/paper.png" , OSL_IN_RAM , OSL_PF_5551);
	title[3]=oslLoadImageFilePNG("graphics/info.png" , OSL_IN_RAM , OSL_PF_5551);
	title[4]=oslLoadImageFilePNG("graphics/bkr.png" , OSL_IN_RAM , OSL_PF_8888);
	title[5]=oslLoadImageFilePNG("graphics/bkr2.png" , OSL_IN_RAM , OSL_PF_8888);
	title[6]=oslLoadImageFilePNG("graphics/street.png" , OSL_IN_RAM , OSL_PF_5551);
	title[7]=oslLoadImageFilePNG("graphics/losing.png" , OSL_IN_RAM , OSL_PF_8888);
	title[8]=oslLoadImageFilePNG("graphics/rules.png" , OSL_IN_RAM , OSL_PF_5551);
	title[9]=oslLoadImageFilePNG("graphics/notfound.png" , OSL_IN_RAM , OSL_PF_5551);
	title[10]=oslLoadImageFilePNG("graphics/credits.png" , OSL_IN_RAM , OSL_PF_5551);
	title[11]=oslLoadImageFilePNG("graphics/wingame.png" , OSL_IN_RAM , OSL_PF_5551);
	title[12]=oslLoadImageFilePNG("graphics/street2.png" , OSL_IN_RAM , OSL_PF_5551);
	GG[1]=oslLoadImageFilePNG("graphics/gg.png" , OSL_IN_RAM , OSL_PF_8888);
	GG[2]=oslLoadImageFilePNG("graphics/gg2.png" , OSL_IN_RAM , OSL_PF_8888);
	oslDrawHealthBar(120,106,240,60,70,100,2);
	graphics[0]=oslLoadImageFilePNG("graphics/press_start.png", OSL_IN_RAM , OSL_PF_5551);
	graphics[1]=oslLoadImageFilePNG("graphics/duck.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[2]=oslLoadImageFilePNG("graphics/bomb.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[3]=oslLoadImageFilePNG("graphics/happy.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[4]=oslLoadImageFilePNG("graphics/verysad.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[5]=oslLoadImageFilePNG("graphics/romb.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[6]=oslLoadImageFilePNG("graphics/tri.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[7]=oslLoadImageFilePNG("graphics/circle.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[8]=oslLoadImageFilePNG("graphics/continue.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[9]=oslLoadImageFilePNG("graphics/frog.png",OSL_IN_RAM , OSL_PF_5551);
	oslDrawHealthBar(120,106,240,60,90,100,2);
	graphics[10]=oslLoadImageFilePNG("graphics/redcar.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[11]=oslLoadImageFilePNG("graphics/bluecar.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[12]=oslLoadImageFilePNG("graphics/greencar.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[13]=oslLoadImageFilePNG("graphics/yellowcar.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[14]=oslLoadImageFilePNG("graphics/Cas.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[15]=oslLoadImageFilePNG("graphics/Sac.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[16]=oslLoadImageFilePNG("graphics/cascaval.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[17]=oslLoadImageFilePNG("graphics/win.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[18]=oslLoadImageFilePNG("graphics/lose.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[19]=oslLoadImageFilePNG("graphics/bow.png",OSL_IN_RAM , OSL_PF_5551);
	graphics[20]=oslLoadImageFilePNG("graphics/car.png",OSL_IN_RAM,OSL_PF_5551);
	graphics[21]=oslLoadImageFilePNG("graphics/gas.png",OSL_IN_RAM,OSL_PF_5551);
	graphics[22]=oslLoadImageFilePNG("graphics/police.png",OSL_IN_RAM,OSL_PF_5551);
	mouse=oslLoadImageFilePNG("graphics/cursor.png",OSL_IN_RAM , OSL_PF_5551);
	mouse->x=226;
	mouse->y=120;
	if(ac[10]!=1)
		time (&start);
	oslDrawHealthBar(120,106,240,60,100,100,2);
	oslEndDrawing();
	oslSyncFrame();
	oslSetTextColor(black);
	oslInitGfx(OSL_PF_8888, 1);
	return 1;
}