#ifndef _YUV_STREAM_H
#define _YUV_STREAM_H

class CYUVStream:CstreamBase
{
	public:
		CYUVStream();
		//����
		 int Open();
		//ȡ������
		 int PopData(YUVData &data);
		//�ر���
		 int Close();
	private:
		FILE *fp;  
		int pixel_w;
		int pixel_h;
		unsigned char *buffer; 
};
#endif