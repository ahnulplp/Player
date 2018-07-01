#ifndef _PLAYEROBJ_H
#define _PLAYEROBJ_H

class CPlayerObj
{
	
	public:
		CPlayerObj();
		void ShowFrame(YUVData data);
		void Close_Win();
		void Reset_Window();
	protected:

	private:
		SDL_Window   *m_screen; 
		SDL_Renderer *m_sdlRenderer; 
		SDL_Texture  *m_sdlTexture ; 
	    int          m_init ;
		Uint32       m_pixformat ; 
		int m_screen_w;
		int m_screen_h;
};
#endif