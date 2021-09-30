#include "TextButton.h"

TextButton::TextButton()
{

}

TextButton::TextButton(SpriteSheet& ss, int tag, Vec2f pos, std::string text,Vec2f offset,SDL_Colour col,TTFont& font):Button(ss,tag,pos)
{
    offset_=offset;
    col_=col;
    text_=text;
    font_=&font;
}

void TextButton::Draw()
{
    Button::Draw();
    font_->Draw(text_,
        (int)GetAABB2D().minX_+offset_.x,
        (int)GetAABB2D().minY_+offset_.y,
        col_);
}
