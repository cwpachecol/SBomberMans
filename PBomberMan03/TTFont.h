#ifndef TTFONT_H_INCLUDED
#define TTFONT_H_INCLUDED

#include <SDL_ttf.h>
#include <string>
class TTFont
{
public:
    TTFont();
    ~TTFont();
    bool Load(const std::string& fontName, int pointSize);
    void Draw(const std::string& text, int x,int y,SDL_Colour col);
private:
    TTF_Font* font_;
};
#endif