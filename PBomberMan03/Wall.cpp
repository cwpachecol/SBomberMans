#include "Wall.h"
#include "TileFunctions.h"

Wall::Wall(Vec2f pos,bool breakable)
{
    sprite_.AssignImage(TheLoadState::Instance()->wall);
    isBreakable_=breakable;
    if(isBreakable_)
    {
        sprite_.SetFrameRange(0,0);
    }
    else
    {
        sprite_.SetFrameRange(1,1);
    }
    sprite_.Stop();
    sprite_.SetPos(Settle(pos));

}

void Wall::Draw()
{
    sprite_.Draw();
}

void Wall::Update()
{
    sprite_.Update();
}

Vec2f Wall::GetPos()const
{
    return sprite_.GetPos();
}

AABB2D Wall::GetAABB2D()const
{
    return sprite_.GetAABB();
}

bool Wall::GetBreakable()const
{
    return isBreakable_;
}