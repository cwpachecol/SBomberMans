#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "Sprite.h"
#include "AABB2D.h"
#include <string>
class Button
{
public:
    Button(SpriteSheet&,int,Vec2f);
    Button();
    virtual void Draw();
    virtual void OnClick();
    virtual void OnOver();
    virtual void OnUp();
    AABB2D GetAABB2D()const;
    int GetTag()const;
private:
    Sprite sprite_;
    int tag_;
};


#endif