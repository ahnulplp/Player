#include "common.h"


void Print_ffmpeg_ConfigInfo()
{
	printf("%s\n",avcodec_configuration());
}