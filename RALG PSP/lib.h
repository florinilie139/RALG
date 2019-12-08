#include <oslib/oslib.h>
#include <algorithm>

using namespace std;

#define blue  RGB(0,0,255)
#define red  RGB(255, 0, 0)
#define green  RGB(0, 159, 0)
#define yellow  RGB(255, 255, 0)
#define black  RGB(0,0,0)
#define gray  RGB(204,204,204)
#define white  RGB(255, 255, 255)
#define orange RGB(252, 165, 3)

int collision(OSL_IMAGE *img1, OSL_IMAGE *img2) 
{
   float img1posX = img1->x-img1->centerX;
   float img1posY = img1->y-img1->centerY;
   float img2posX = img2->x-img2->centerX;
   float img2posY = img2->y-img2->centerX;
   float img1width  = img1->stretchX;
   float img1height = img1->stretchY;
   float img2width  = img2->stretchX;
   float img2height = img2->stretchY;
   
   if ((img1posX + img1width > img2posX) && (img1posX < img2posX + img2width) && (img1posY + img1height > img2posY) && (img1posY < img2posY + img2height) )
         return 1;                 
   return 0;
}
void FailCallback(const char *filename, u32 reserved)
{
	//Display an error
	oslFatalError("Unable to locate the following file: %s\nPlease reinstall the application.", filename);
	//Always quit because we can't continue without these precious files
	oslQuit();
}

void oslDrawHealthBar(int x,int y,int width,int height, int health,int max,int type)
{
	int procent=health*100/max;
	procent=width*procent/100;
	if(type==1){
		if(procent>75)
			oslDrawFillRect(x,y,x+procent,y+height,green);
		else if(procent>50)
			oslDrawFillRect(x,y,x+procent,y+height,yellow);
		else if(procent>25)
			oslDrawFillRect(x,y,x+procent,y+height,orange);
		else if(procent>0)
			oslDrawFillRect(x,y,x+procent,y+height,red);
	}
	else if(type==2)
	{
		if(procent>75)
			oslDrawFillRect(x,y,x+procent,y+height,blue);
		else if(procent>50)
			oslDrawFillRect(x,y,x+procent,y+height,RGB(70,70,255));
		else if(procent>25)
			oslDrawFillRect(x,y,x+procent,y+height,RGB(180,180,255));
		else if(procent>0)
			oslDrawFillRect(x,y,x+procent,y+height,RGB(255,255,255));
	}
}