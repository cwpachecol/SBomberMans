#include "TTFont.h"
#include "Screen.h"

TTFont::TTFont()
{
    font_=0;
}

TTFont::~TTFont()
{
    TTF_CloseFont(font_);
}

bool TTFont::Load(const std::string& filename, int size)
{
    font_=TTF_OpenFont(filename.c_str(), size);
    return(font_!=0);
}

void TTFont::Draw(const std::string& text, int x,int y,SDL_Colour col)
{
    SDL_Surface* image= TTF_RenderText_Blended(font_,text.c_str(),col);
    SDL_Rect r={x,y,0,0};
    SDL_BlitSurface(image,0,TheScreen::Instance()->GetScreen(),&r);
    SDL_FreeSurface(image);
}