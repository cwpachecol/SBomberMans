#include "Button.h"


Button::Button(SpriteSheet& sSheet,int tag,Vec2f pos)
{
    sprite_.AssignImage(sSheet);
    sprite_.Stop();
    sprite_.SetPos(pos);
    tag_=tag;
}

Button::Button()
{
    tag_=0;
}

void Button::OnClick()
{
    sprite_.SetFrameRange(2,2);
}

void Button::OnOver()
{
    sprite_.SetFrameRange(1,1);
}

void Button::OnUp()
{
    sprite_.SetFrameRange(0,0);
}

void Button::Draw()
{
    sprite_.Draw();

}

AABB2D Button::GetAABB2D()const
{
    return sprite_.GetAABB();
}

int Button::GetTag()const
{
    return tag_;
}