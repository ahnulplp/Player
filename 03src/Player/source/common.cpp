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

int g_input_th =1;
int g_play_th =1;
SDL_Thread * handle_input_th = NULL;
SDL_Thread * handle_play_th  = NULL;
void Common_init()
{
	CPicMgr::GetInstance()->Init();
	printf("Common_init end\n");
}

void Common_uninit()
{
	g_input_th = 0;
	g_play_th  = 0;
	int th_status;
	SDL_WaitThread(handle_input_th,&th_status);
	SDL_WaitThread(handle_play_th,&th_status);
	// 两个线程 退出后 CPicMgr的内存 要释放
	SDL_Quit();
	CPicMgr::GetInstance()->ClearAllData();
	CPicMgr::GetInstance()->UnInit();
}