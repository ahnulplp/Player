#include "common.h"

int main_t()
{
	//Print_ffmpeg_ConfigInfo();
	// Player_SDLInfo();


	Common_init();

	handle_input_th = SDL_CreateThread(input_th,NULL,NULL);
	handle_timer_th  = SDL_CreateThread(timer_th,NULL,NULL);
	handle_play_th  = SDL_CreateThread(play_th,NULL,NULL);
	
	printf("Press any key to exit:");
	getchar();
	Common_uninit();
	return 0;
}