#ifndef _STREAM_BASE_H
#define _STREAM_BASE_H

class CstreamBase
{
	public:
		//����
		virtual int Open();
		//ȡ������
		virtual int PopData(YUVData &data);
		//�ر���
		virtual int Close();
	private:
};
#endif