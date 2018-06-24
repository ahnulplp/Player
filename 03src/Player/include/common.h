#include <stdio.h>
extern "C"
{
	#include "ffmpeg/libavcodec/avcodec.h"
	#include "ffmpeg/libavformat/avformat.h"
	#include "ffmpeg/libswscale/swscale.h"
	#include "ffmpeg/libavutil/imgutils.h"

	#include "SDL2/SDL.h"  
};


#define SDL2_LIB(libname) "../../../01lib/third_lib/SDL2/"libname
#define FFMPEG_LIB(libname) "../../../01lib/third_lib/ffmpeg/"libname

void Print_ffmpeg_ConfigInfo();
void Player_SDLInfo();
