class object{
	public:
		double fx1,fy1,fx2,fy2;
		double mx,my;
		double tx,ty;
		char txt[50];
		int text;
		int bounce;
		int frame,type,aux,On,moveble,big;
		OSL_IMAGE *image;
		bool is_off_screen (void){
			if(image->x+image->stretchX<0 || image->x>480 || image->y+image->stretchY<0 || image->y>272)
				return 1;
			return 0;
		}
		void update (void){
			image->x+=mx;
			image->y+=my;
			if(bounce==1){
				if(image->x<0 || image->x+image->stretchX>480)
					mx*=-1;
				if(image->y<0 || image->y+image->stretchY>272)
					my*=-1;
			}
			if(bounce==2){
				if(image->x+image->stretchX<0)
					image->x+=480+image->stretchX;
				if(image->x>480)
					image->x-=480+image->stretchX;
				if(image->y+image->stretchY<0)
					image->y+=272+image->stretchY;
				if(image->y>272)
					image->y-=272+image->stretchY;
			}
		}
		bool touched (void){
			if(osl_pad.pressed.cross && collision(image,mouse))
				return 1;
			return 0;
		}
		bool moving (void){
			if(move_enable==1 && osl_pad.pressed.square && collision(image,mouse) && move==0 && moveble){
				osl_pad.pressed.square=0;
				return 1;
			}
			return 0;
		}
		void texting (void){
			if(text==1){
				if(big==1)
					oslSetFont(big_font);
				oslPrintf_xy(image->x+tx,image->y+ty,txt);
				oslSetFont(font);
			}
		}
		void debug(int i){
			if(collision(mouse,image)==1 && debugON==1){
				oslPrintf_xy(mouse->x+16,mouse->y	  ,"ID:%d  B:%d",i,bounce);
				oslPrintf_xy(mouse->x+16,mouse->y+10," X:%d  Y:%d"	,image->x,image->y);
				oslPrintf_xy(mouse->x+16,mouse->y+20,"SX:%d SY:%d",image->stretchX,image->stretchY);
				oslPrintf_xy(mouse->x+16,mouse->y+30,"ax:%d MV:%d",aux,moveble);
				debugON=2;
			}
		}
};