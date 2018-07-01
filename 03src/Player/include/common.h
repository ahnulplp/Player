#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
#include "struct.h"

extern "C"
{
	#include "ffmpeg/libavcodec/avcodec.h"
	#include "ffmpeg/libavformat/avformat.h"
	#include "ffmpeg/libswscale/swscale.h"
	#include "ffmpeg/libavutil/imgutils.h"

	#include "SDL2/SDL.h"  
};

#define REFRESH_EVENT  (SDL_USEREVENT + 1)  
//Break  
#define BREAK_EVENT  (SDL_USEREVENT + 2) 

#include "PicMgr.h"
#include "playerObj.h"
#include "StreamBase.h"
#include "YUVStream.h"
#include "VideoStream.h"
#define PIC_SUM  1024
#define SDL2_LIB(libname) "../../../01lib/third_lib/SDL2/"libname
#define FFMPEG_LIB(libname) "../../../01lib/third_lib/ffmpeg/"libname

extern int g_input_th;
extern int g_timer_th;
extern int g_play_th;
extern SDL_Thread * handle_input_th;
extern SDL_Thread * handle_play_th;
extern SDL_Thread * handle_timer_th;

void Common_init();
void Common_uninit();
void Print_ffmpeg_ConfigInfo();
void Player_SDLInfo();
#define SAFE_DELETE(var) \
	if (var)\
	{\
	delete var;\
	var = NULL;\
}
int input_th(void *arg);
int timer_th(void *arg);
int play_th(void *arg);


#endif