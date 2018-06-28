#include "common.h"


int input_th(void *arg)
{
	FILE *fp = NULL;  
	static int pixel_w = 512;
	static int pixel_h = 288;
	unsigned char buffer[512*288*12 / 8]; 
	fp = fopen("512_288output.yuv", "rb+");

	if (fp == NULL)
	{  
		printf("cannot open this file\n");  
		return -1;
	}  
	while(g_input_th)
	{
		if (fread(buffer, 1, pixel_w*pixel_h*12 / 8, fp) != pixel_w*pixel_h*12 / 8)
		{  
			// Loop  
			fseek(fp, 0, SEEK_SET); 
			g_input_th = 0;
			fread(buffer, 1, pixel_w*pixel_h*12 / 8, fp);  
		}  
		YUVData data;
		data.datasize = pixel_w*pixel_h*12/8;
		data.pdata = new char[data.datasize];
		memcpy(data.pdata,buffer,data.datasize);
		data.height = pixel_h;
		data.width  = pixel_w;
		CPicMgr::GetInstance()->PushData(data);
		SDL_Event th_event;  
		th_event.type = REFRESH_EVENT; 
		SDL_PushEvent(&th_event);  //发送一个事件 
		SDL_Delay(40);
	}

	fclose(fp);
	SDL_Event th_event;  
	th_event.type = BREAK_EVENT; 
	SDL_PushEvent(&th_event);  //发送一个事件 
	return 0;
}