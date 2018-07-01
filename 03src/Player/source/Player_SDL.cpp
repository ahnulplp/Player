#include "common.h"

int play_th(void *arg)
{
	YUVData data;
	SDL_Event th_event; 
	CPlayerObj playerObj;
	while(g_play_th)
	{
		SDL_WaitEvent(&th_event);
		if (th_event.type == REFRESH_EVENT)
		{  
			if (CPicMgr::GetInstance()->PopForntData(data))
			{
				playerObj.ShowFrame(data);
				SAFE_DELETE(data.pdata);
			}
		}
		else if (th_event.type == SDL_QUIT || th_event.type == BREAK_EVENT ) 
		{ 
			playerObj.Close_Win();
			break;  
		}  
		else if (th_event.type == SDL_WINDOWEVENT) 
		{  
			//If Resize  
			playerObj.Reset_Window();
		}  
		else 
		{

		}
	}
	
	printf("g_play_th exit\n");
	return 0;
}

void Player_SDLInfo()
{
	SDL_version compiled;
	SDL_version linked;
	
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d \n",
		compiled.major, compiled.minor, compiled.patch);
	printf("But we linked against SDL version %d.%d.%d\n",
		linked.major, linked.minor, linked.patch);
}
