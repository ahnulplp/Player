#ifndef _FILE_VIDEO_STREAM_H
#define _FILE_VIDEO_STREAM_H

class CVideoStream:CstreamBase
{
public:
	CVideoStream();
	//����
	int Open();
	//ȡ������
	int PopData(YUVData &data);
	//�ر���
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