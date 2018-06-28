#include "common.h"


void Show_Frame(YUVData data)
{
	static SDL_Window *screen; 
	static SDL_Renderer* sdlRenderer; 
	static SDL_Texture * sdlTexture ; 
	static int screen_init = 0;
	static Uint32 pixformat = 0;  

	int screen_w  = data.width;
	int screen_h  = data.height;
	if (screen_init == 0 )
	{
		screen = SDL_CreateWindow("Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
			screen_w, screen_h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);  
		if (!screen) 
		{  
			printf("SDL: could not create window - exiting:%s\n", SDL_GetError());  
			return;  
		}  
		//创建渲染器
		sdlRenderer = SDL_CreateRenderer(screen, -1, 0);  

		//IYUV: Y + U + V  (3 planes)  
		//YV12: Y + V + U  (3 planes)  
		pixformat = SDL_PIXELFORMAT_IYUV;  
		sdlTexture = SDL_CreateTexture(sdlRenderer, pixformat, SDL_TEXTUREACCESS_STREAMING, screen_w, screen_h);
		screen_init = 1; 
	}
	//设置纹理的数据  
	SDL_UpdateTexture(sdlTexture, NULL, data.pdata, screen_w); 
	SDL_Rect srcRect[4];  
	SDL_Rect sdlRect;  
	sdlRect.x = 0;  
	sdlRect.y = 0;  
	sdlRect.w = screen_w;  
	sdlRect.h = screen_h;  

	SDL_RenderClear(sdlRenderer);  
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &sdlRect);  
	//显示  
	SDL_RenderPresent(sdlRenderer);
	
}
int play_th(void *arg)
{
	if (SDL_Init(SDL_INIT_VIDEO)) 
	{  
		printf("Could not initialize SDL2 - %s\n", SDL_GetError());
		return -1;
	} 
	YUVData data;
	SDL_Event th_event;  
	while(g_play_th)
	{
		SDL_WaitEvent(&th_event); 
		if (th_event.type == REFRESH_EVENT)
		{  
			if (CPicMgr::GetInstance()->PopForntData(data))
			{
				Show_Frame(data);
				SAFE_DELETE(data.pdata);
			}
		}
		else if (th_event.type == SDL_QUIT || th_event.type == BREAK_EVENT ) 
		{  
			break;  
		}   
		else 
		{

		}
	}
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
