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

	UINT32 Init(); // ��ʼ���߳� ���� ��ֹ ���̻߳�Ҫ����
	UINT32 UnInit();// ��ʼ�����߳� ����
private:
	SDL_mutex * m_mutex;
	static CPicMgr* m_pInstance;
     CPicMgr();
	~CPicMgr();
	list<YUVData> m_vYuvData;
};
#endif