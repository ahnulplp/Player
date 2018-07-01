#include "common.h"

int CVideoStream::Open()
{
	char * filePath = "cuc_ieschool.flv";
	av_register_all();
	pFormatCtx = avformat_alloc_context();
	if (avformat_open_input(&pFormatCtx,filePath,NULL,NULL))
	{
		printf("avformat_open_input %s not open\n",filePath);
			return -1;
	}

	if (avformat_find_stream_info(pFormatCtx,NULL))
	{
		printf("avformat_find_stream_info %s not open\n",filePath);
			return -1;
	}

	//找到视频的 下标
	videoIndex =-1;
	for (int i=0;i<pFormatCtx->nb_streams;i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoIndex = i;
			break;
		}
	}

	if (videoIndex == -1)
	{
		printf(" AVMEDIA_TYPE_VIDEO  not find\n");
		return -1;
	}

	pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
	pCodec    = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		printf(" avcodec_find_decoder  not find\n");
		return -1;
	}

	if (avcodec_open2(pCodecCtx,pCodec,NULL) < 0)
	{
		printf("Could not open codec.\n");
		return -1;
	}

	pFrame = av_frame_alloc();
	pPacket = av_packet_alloc();
	 pFrameYUV = av_frame_alloc();
	printf("------------------------------------------------------\n");
	av_dump_format(pFormatCtx,NULL,filePath,NULL);
	printf("------------------------------------------------------\n");

	out_buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	// 为已经分配空间的结构体AVPicture挂上一段用于保存数据的空间
	// AVFrame/AVPicture有一个data[4]的数据字段,buffer里面存放的只是yuv这样排列的数据，
	// 而经过fill 之后，会把buffer中的yuv分别放到data[0],data[1],data[2]中。
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);

	//// 参数：源图像的宽，源图像的高，源图像的像素格式，目标图像的宽，目标图像的高，目标图像的像素格式，设定图像拉伸使用的算法
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	return 0;

}

int CVideoStream::PopData( YUVData &data )
{
	int av_ret,got_picture,ret =-1;
	if(av_read_frame(pFormatCtx, pPacket) >= 0 )
	{
		if(pPacket ->stream_index == videoIndex)
		{
			av_ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, pPacket);
			if(av_ret < 0)
			{
				printf("Decode Error.\n");
				return -1;
			}
			if(got_picture)
			{
				// 转换像素
				sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
					pFrameYUV->data, pFrameYUV->linesize);
				data.height = pFrame->height;
				data.width =  pFrame->width;
				data.datasize = (data.height*data.width)*3/2;
				data.pdata = new char[data.datasize];
				memcpy(data.pdata, pFrameYUV->data[0], data.height*data.width);
				memcpy(data.pdata + data.height*data.width, pFrameYUV->data[1], data.height*data.width / 4);
				memcpy(data.pdata + data.height*data.width*5/4, pFrameYUV->data[2], data.height*data.width / 4);
				ret = 0;
			}
		}
		av_free_packet(pPacket);
	}
	else 
	{
		return -1;
	}
	return ret;
}

int CVideoStream::Close()
{
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	return 0;
}

CVideoStream::CVideoStream()
{

}
