#include "common.h"


#pragma comment(lib,FFMPEG_LIB("avcodec.lib"))
#pragma comment(lib,FFMPEG_LIB("avdevice.lib"))
#pragma comment(lib,FFMPEG_LIB("avfilter.lib"))
#pragma comment(lib,FFMPEG_LIB("avformat.lib"))
#pragma comment(lib,FFMPEG_LIB("avutil.lib"))
#pragma comment(lib,FFMPEG_LIB("postproc.lib"))
#pragma comment(lib,FFMPEG_LIB("swresample.lib"))
#pragma comment(lib,FFMPEG_LIB("swscale.lib"))


#pragma comment(lib,SDL2_LIB("SDL2.lib"))
#pragma comment(lib,SDL2_LIB("SDL2main.lib"))
#pragma comment(lib,SDL2_LIB("SDL2test.lib"))

int g_input_th = 1;
int g_play_th  = 1;
int g_timer_th = 1;

SDL_Thread * handle_input_th = NULL;
SDL_Thread * handle_play_th  = NULL;
SDL_Thread * handle_timer_th = NULL;

void Common_init()
{
	CPicMgr::GetInstance()->Init();
	
	if (SDL_Init(SDL_INIT_VIDEO)) 
	{  
		printf("Could not initialize SDL2 - %s\n", SDL_GetError());
	} 

	printf("Common_init end\n");

}

void Common_uninit()
{
	g_input_th = 0;
	g_play_th  = 0;
	g_timer_th  = 0;
	int th_status = -1;

	SDL_WaitThread(handle_timer_th,&th_status);
	SDL_WaitThread(handle_input_th,&th_status);
	SDL_WaitThread(handle_play_th,&th_status);

	// 两个线程 退出后 CPicMgr的内存 要释放
	SDL_Quit();

	CPicMgr::GetInstance()->ClearAllData();
	CPicMgr::GetInstance()->UnInit();
	printf("Common_uninit end \n");
}

int timer_th(void *arg)
{
	SDL_Event th_event;
	while(g_timer_th)
	{
		th_event.type = REFRESH_EVENT; 
		SDL_PushEvent(&th_event);  //发送一个事件 
		SDL_Delay(40);
	}
	th_event.type = BREAK_EVENT; 
	SDL_PushEvent(&th_event);  //发送一个事件
	printf("timer_th exit\n");
	return 0;
}
