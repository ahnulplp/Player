#ifndef _FILE_VIDEO_STREAM_H
#define _FILE_VIDEO_STREAM_H

class CVideoStream:CstreamBase
{
public:
	CVideoStream();
	//打开流
	int Open();
	//取出数据
	int PopData(YUVData &data);
	//关闭流
	int Close();
private:
	AVFormatContext *pFormatCtx;  
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFrame         *pFrame;
	AVPacket        *pPacket;
	AVFrame         *pFrameYUV;
	int videoIndex;
	uint8_t * out_buffer;
	struct SwsContext *img_convert_ctx;
};

#endif