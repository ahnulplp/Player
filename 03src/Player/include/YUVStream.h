#ifndef _YUV_STREAM_H
#define _YUV_STREAM_H

class CYUVStream:CstreamBase
{
	public:
		CYUVStream();
		//打开流
		 int Open();
		//取出数据
		 int PopData(YUVData &data);
		//关闭流
		 int Close();
	private:
		FILE *fp;  
		int pixel_w;
		int pixel_h;
		unsigned char *buffer; 
};
#endif