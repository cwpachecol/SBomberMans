#ifndef TEXTBUTTON_H_INCLUDED
#define TEXTBUTTON_H_INCLUDED
#include "Button.h"
#include "TTFont.h"

class TextButton:public Button
{
public:
    TextButton(SpriteSheet& ss,int tag,Vec2f pos,std::string text,Vec2f offset,SDL_Colour col,TTFont& font);
    TextButton();
    virtual void Draw();
private:
    TTFont* font_;
    std::string text_;
    SDL_Colour col_;
    Vec2f offset_;

};

#endif