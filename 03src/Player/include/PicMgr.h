#ifndef  _PICMGR_H
#define _PICMGR_H

class CPicMgr
{
public:
	static CPicMgr* GetInstance();
	void DestroyInstance();

	void PushData(YUVData yuvData);
	int PopForntData(YUVData &yuvData);
	void ClearAllData();

	UINT32 Init(); // 初始化线程 调用 防止 多线程还要加锁
	UINT32 UnInit();// 初始化的线程 调用
private:
	SDL_mutex * m_mutex;
	static CPicMgr* m_pInstance;
     CPicMgr();
	~CPicMgr();
	list<YUVData> m_vYuvData;
};
#endif