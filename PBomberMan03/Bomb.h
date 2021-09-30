#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED
#include "Sprite.h"


class Bomb
{
public:
    Bomb(int power, float fuse,Vec2f& pos,SpriteSheet& ssr,int owner);
    void Update();
    void Draw();
    Vec2f GetPos()const;
    int GetTag()const;
    int GetPower()const;
    bool HasExploded()const;
private:
    int owner_;
    int power_;
    float fuse_;
    Sprite bombSprite_;
};

#endif