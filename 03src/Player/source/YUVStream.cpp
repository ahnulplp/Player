#include "common.h"

CYUVStream::CYUVStream()
{
	fp = NULL;  
	pixel_w = 0;
	pixel_h = 0;
	buffer = NULL; 
}

int CYUVStream::Open()
{
	fp = fopen("352x288_my.yuv", "rb+");
	pixel_w = 352;
	pixel_h = 288;
	if (fp == NULL)
	{  
		printf("cannot open this file\n");  
		return -1;
	}  
	buffer = new unsigned char[pixel_w*pixel_h*12/8];
	return 0;
}


int CYUVStream::PopData(YUVData &data)
{
	int ret = fread(buffer, 1, pixel_w*pixel_h*12 / 8, fp);
	if (ret != pixel_w*pixel_h*12 / 8)
	{  
		// Loop  
		fseek(fp, 0, SEEK_SET); 
		fread(buffer, 1, pixel_w*pixel_h*12 / 8, fp);  
	}  
	data.datasize = pixel_w*pixel_h*12/8;
	data.pdata = new char[data.datasize];
	memcpy(data.pdata,buffer,data.datasize);
	data.height = pixel_h;
	data.width  = pixel_w;
	return 0;
}

int CYUVStream::Close()
{
	if (fp)
	{  
		fclose(fp);
	}  
	SAFE_DELETE(buffer);
	return 0;
}