#ifndef _STREAM_BASE_H
#define _STREAM_BASE_H

class CstreamBase
{
	public:
		//打开流
		virtual int Open();
		//取出数据
		virtual int PopData(YUVData &data);
		//关闭流
		virtual int Close();
	private:
};
#endif