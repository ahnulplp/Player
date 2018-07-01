#include "common.h"

void CPlayerObj::ShowFrame(YUVData data)
{
	if (m_init == 0 )
	{
		m_screen_w = data.width;  
		m_screen_h = data.height; 
		m_screen = SDL_CreateWindow("Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
									data.width, data.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);  
		if (!m_screen) 
		{  
			printf("SDL: could not create window - exiting:%s\n", SDL_GetError());  
			return;  
		}  
		//创建渲染器
		m_sdlRenderer = SDL_CreateRenderer(m_screen, -1, 0);  

		//IYUV: Y + U + V  (3 planes)  
		//YV12: Y + V + U  (3 planes)  
		m_pixformat = SDL_PIXELFORMAT_IYUV;  
		m_sdlTexture = SDL_CreateTexture(m_sdlRenderer, m_pixformat, SDL_TEXTUREACCESS_STREAMING, m_screen_w, m_screen_h);
		m_init = 1; 
	}
	//设置纹理的数据  
	SDL_UpdateTexture(m_sdlTexture, NULL, data.pdata, data.width); 
	SDL_Rect srcRect[4];  
	SDL_Rect sdlRect;  
	sdlRect.x = 0;  
	sdlRect.y = 0;  
	sdlRect.w = m_screen_w;  
	sdlRect.h = m_screen_h;  

	SDL_RenderClear(m_sdlRenderer);  
	SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, NULL, &sdlRect);  
	//显示  
	SDL_RenderPresent(m_sdlRenderer);
}

void CPlayerObj::Close_Win()
{
	if (m_init)
	{
		SDL_DestroyTexture(m_sdlTexture);
		SDL_DestroyRenderer(m_sdlRenderer);
		SDL_DestroyWindow(m_screen);
	}
}

CPlayerObj::CPlayerObj()
{
	m_screen = NULL; 
	m_sdlRenderer  = NULL; 
	m_sdlTexture  = NULL; 
	m_init = 0;
	m_pixformat = 0; 
}

void CPlayerObj::Reset_Window()
{
	//If Resize  
	SDL_GetWindowSize(m_screen, &m_screen_w, &m_screen_h); 
}
