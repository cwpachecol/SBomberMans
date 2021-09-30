#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
#include "Vec2.h"
#include "Sprite.h"
#include "LoadState.h"
class Wall
{
public:
    Wall(Vec2f pos,bool breakable);
    void Draw();
    void Update();
    Vec2f GetPos()const;
    AABB2D GetAABB2D()const;
    bool GetBreakable()const;

private:
    Sprite sprite_;
    bool isBreakable_;
};

#endif