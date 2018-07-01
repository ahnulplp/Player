#include "common.h"


int input_th(void *arg)
{
	//CstreamBase *pStream = (CstreamBase *)new CYUVStream();
	CstreamBase *pStream = (CstreamBase *)new CVideoStream();

	if (pStream->Open() != 0)
	{
		return -1;
	}
	while(g_input_th)
	{
		YUVData data;
		if (pStream->PopData(data) == 0)
		{
			CPicMgr::GetInstance()->PushData(data);
		}
		SDL_Delay(10);
	}
	pStream->Close();
	printf("g_input_th exit\n");
	return 0;
}