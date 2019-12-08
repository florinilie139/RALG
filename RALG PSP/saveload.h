struct oslSaveLoad saveLoadData;

char gameTitle[50] = "Really Annoying Level Game";
char gameID[10] = "ULES0RALG";
char saveName[10] = "1139";

char nameList[][20] =
{
 "00", "01", "02", "03", "04", ""
};

void save ()
{
	int type = OSL_DIALOG_NONE;
    int skip = 0;
	char data[500];
	int ok=0;
	char aux[100];
	sprintf(aux,"total_levels = %d\n",tlvl);
	strcpy(data,aux);
	sprintf(aux,"total_infinite = %d\n",tilvl);
	strcat(data,aux);
	sprintf(aux,"random_option = %d\n",rndlvl);
	strcat(data,aux);
	sprintf(aux,"time = %d\n",time_elapsed);
	strcat(data,aux);
	sprintf(aux,"loses = %d\n",tl);
	strcat(data,aux);
	sprintf(aux,"analog = %d\n",analog);
	strcat(data,aux);
	sprintf(aux,"loses = %d\n",loses);
	strcat(data,aux);
	for(int i=1;i<11;i++){
		sprintf(aux,"high_score%d= %d\n",i,hi[i]);
		strcat(data,aux);
	}
	for(int i=1;i<11;i++){
		sprintf(aux,"ac%d = %d\n",i,ac[i]);
		strcat(data,aux);
	}

	while(!osl_quit){
		type = oslGetSaveLoadType();

		if (!skip){
            oslStartDrawing();
			oslDrawFillRect(0,0,480,272,black);
            if (type != OSL_DIALOG_NONE){
                oslDrawSaveLoad();
				
                if (oslGetLoadSaveStatus() == PSP_UTILITY_DIALOG_NONE){
					if (oslSaveLoadGetResult() == OSL_SAVELOAD_CANCEL && ok==1)
						break;
					else if (type == OSL_DIALOG_SAVE && ok==1)
                        break;
                    oslEndSaveLoadDialog();
                }
            }
            oslEndDrawing();
        }
        if (type == OSL_DIALOG_NONE){
            memset(&saveLoadData, 0, sizeof(saveLoadData));
			strcpy(saveLoadData.gameTitle, gameTitle);
			strcpy(saveLoadData.gameID, gameID);
			strcpy(saveLoadData.saveName, saveName);
			saveLoadData.nameList = nameList;
			saveLoadData.icon0 = icon0;
			saveLoadData.size_icon0 = size_icon0;
			saveLoadData.data = data;
			saveLoadData.dataSize = 500;
			oslInitSaveDialog(&saveLoadData);
			ok=1;
        }
        oslEndFrame();
        skip = oslSyncFrame();
    }
	
}
void load()
{
	int type = OSL_DIALOG_NONE;
    int skip = 0;
	char loadedData [500];
	while(!osl_quit){
		type = oslGetSaveLoadType();

		if (!skip){
            oslStartDrawing();
			oslDrawFillRect(0,0,480,272,black);
			if (type != OSL_DIALOG_NONE){
                oslDrawSaveLoad();
				if (oslGetLoadSaveStatus() == PSP_UTILITY_DIALOG_NONE){
					if (oslSaveLoadGetResult() == OSL_SAVELOAD_CANCEL)
                        return;
					else if (type == OSL_DIALOG_LOAD && oslSaveLoadGetResult()==OSL_SAVELOAD_OK){
						sscanf(loadedData,"total_levels = %d",&tlvl);
						char* pointer=strchr(loadedData,10);
						sscanf(pointer+1,"total_infinite = %d",&tilvl);
						pointer=strchr(pointer+1,10);
						sscanf(pointer+1,"random_option = %d",&rndlvl);
						pointer=strchr(pointer+1,10);
						sscanf(pointer+1,"time = %d",&time_elapsed);
						pointer=strchr(pointer+1,10);
						sscanf(pointer+1,"loses = %d",&tl);
						pointer=strchr(pointer+1,10);
						sscanf(pointer+1,"analog = %d",&analog);
						pointer=strchr(pointer+1,10);
						sscanf(pointer+1,"loses= %d",&lose);
						pointer=strchr(pointer+1,10);
						for(int i=1;i<11;i++){
							sscanf(pointer+1,"high_score%d= %d",&i,&hi[i]);
							pointer=strchr(pointer+1,10);
						}
						for(int i=1;i<11;i++){
							sscanf(pointer+1,"ac%d = %d",&i,&ac[i]);
							pointer=strchr(pointer+1,10);
						}
						oslSetKeyAnalogToDPad(analog);
						return;
					}
					else return;
                    oslEndSaveLoadDialog();
                }
			}
            oslEndDrawing();
		}
		if (type == OSL_DIALOG_NONE){
			memset(&saveLoadData, 0, sizeof(saveLoadData));
			strcpy(saveLoadData.gameID, gameID);
			strcpy(saveLoadData.saveName, saveName);
			saveLoadData.nameList = nameList;
			saveLoadData.data = &loadedData;
			saveLoadData.dataSize = 500;
			oslInitLoadDialog(&saveLoadData);
		}
        oslEndFrame();
        skip = oslSyncFrame();
    }
	
}