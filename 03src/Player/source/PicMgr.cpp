#include "common.h"
// 单例对象初始化
CPicMgr* CPicMgr::m_pInstance = NULL;

CPicMgr* CPicMgr::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CPicMgr();
	}
	return m_pInstance;
}

void CPicMgr::DestroyInstance()
{
	 SAFE_DELETE(m_pInstance);
}

UINT32 CPicMgr::Init()
{
	return 0;
}

UINT32 CPicMgr::UnInit()
{
	DestroyInstance();
	return 0;
}

CPicMgr::CPicMgr()
{
	m_mutex = SDL_CreateMutex();
}

CPicMgr::~CPicMgr()
{
	ClearAllData();
}

void CPicMgr::PushData(YUVData yuvData)
{
	SDL_LockMutex(m_mutex);
	//Lock 
	if (m_vYuvData.size() > PIC_SUM)
	{
		yuvData = m_vYuvData.front();
		SAFE_DELETE(yuvData.pdata);
		m_vYuvData.pop_front();
	}
	m_vYuvData.push_back(yuvData);
	SDL_UnlockMutex(m_mutex);
	//UnLock 
}

int CPicMgr::PopForntData(YUVData &yuvData)
{
	int ret = 0; 
	//Lock 
	SDL_LockMutex(m_mutex);
	if (m_vYuvData.size() > 0)
	{
		yuvData = m_vYuvData.front();
		m_vYuvData.pop_front();
		ret = 1;
	}
	//UnLock
	SDL_UnlockMutex(m_mutex);
	return ret;
}

void CPicMgr::ClearAllData()
{
	//Lock 
	SDL_LockMutex(m_mutex);
	while (m_vYuvData.size() > 0)
	{
		YUVData yuvData = m_vYuvData.front();
		SAFE_DELETE(yuvData.pdata);
		m_vYuvData.pop_front();
	}
	//UnLock
	SDL_UnlockMutex(m_mutex);
	//UnLock
}



