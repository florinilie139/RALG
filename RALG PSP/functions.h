void DrawAchievement(){
	if(acu.On!=0)
	{
		if(acu.On==2){
			oslDrawGradientRect(acu.fx1,acu.fy1,acu.fx1+160,acu.fy1+78,black,red,red,black);
			oslDrawImage(acu.image);
			oslSetFont(big_font);
			oslPrintf_xy(acu.fx1+70,acu.fy1+20,ACUnlocked[0]);
			oslPrintf_xy(acu.fx1+75,acu.fy1+40,ACUnlocked[1]);
			oslSetFont(font);
			acu.image->y=acu.fy1+5;
			acu.fy1+=acu.my;
			if(acu.aux>0){
				acu.aux--;
				if(acu.aux==0)
					acu.my=1;
			}
			if(acu.fy1==200 && acu.frame==0){
				acu.my=0;
				acu.aux=75*5;
				acu.frame=1;
			}
			if(acu.fy1==272 && acu.frame==1)
				acu.On=3;
		}else if(acu.On==3){
			oslDeleteImage(acu.image);
			if(strlen(acu.txt)!=0)
			{
				acu.aux=acu.txt[0];
				strcpy(acu.txt,acu.txt+1);
				acu.frame=0;
				acu.On=1;
			}
			else
				memset(&acu,0,sizeof(acu));
		}else{
			acu.image=oslCreateImageCopy(achievements[acu.aux],OSL_IN_RAM);
			acu.image->stretchX=60;
			acu.image->stretchY=60;
			ac[acu.aux]=1;
			acu.fx1=320;
			acu.fy1=272;
			acu.image->x=acu.fx1+5;
			acu.image->y=acu.fy1+5;
			acu.my=-1;
			acu.On=2;
			acu.aux=0;
		}
	}
}
void transition(OSL_IMAGE *aux_image,int type)
{
	switch(type){
		case 1:
			aux_image->x=480;
			while(aux_image->x>=0)
			{
				oslStartDrawing();
				oslDrawImage(aux_image);
				aux_image->x-=10;
				oslEndDrawing();
				oslSyncFrame();
			}
			aux_image->x=0;
			break;
		case 2:
			aux_image->x=-480;
			while(aux_image->x<=0)
			{
				oslStartDrawing();
				oslDrawImage(aux_image);
				aux_image->x+=10;
				oslEndDrawing();
				oslSyncFrame();
			}
			aux_image->x=0;
			break;
		case 3:
			aux_image->y=272;
			while(aux_image->y>=0)
			{
				oslStartDrawing();
				oslDrawImage(aux_image);
				aux_image->y-=4;
				oslEndDrawing();
				oslSyncFrame();
			}
			aux_image->y=0;
			break;
		case 4:
			aux_image->y=-272;
			while(aux_image->y<=0)
			{
				oslStartDrawing();
				oslDrawImage(aux_image);
				aux_image->y+=4;
				oslEndDrawing();
				oslSyncFrame();
			}
			aux_image->y=0;
			break;
		case 5:
			aux_image->stretchX=30;
			aux_image->stretchY=17;
			aux_image->centerX=aux_image->sizeX / 2;
			aux_image->centerY=aux_image->sizeY / 2;
			aux_image->x=480/2;
			aux_image->y=272/2;
			while(aux_image->stretchX<480)
			{
				oslStartDrawing();
				oslDrawImage(aux_image);
				aux_image->stretchX+=7.5;
				aux_image->stretchY+=4.25;
				oslEndDrawing();
				oslSyncFrame();
			}
			aux_image->stretchX=480;
			aux_image->stretchY=272;
			aux_image->centerX=0;
			aux_image->centerY=0;
			aux_image->x=0;
			aux_image->y=0;
			break;
		default:
			break;
	}
}
void fnc_menu()
{
	select[0]->x=181;
	select[0]->y=13;
	select[1]->x=20;
	select[1]->y=71;
	select[2]->x=351;
	select[2]->y=75;
	select[3]->x=213;
	select[3]->y=151;
	select[4]->x=90;
	select[4]->y=201;
}
void fnc_achievements(int x)
{
	if(acu.On==0){
		acu.On=1;
		acu.aux=x;
	}
	else
		acu.txt[strlen(acu.txt)]=(char)x;
}

