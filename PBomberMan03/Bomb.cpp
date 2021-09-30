#include "Bomb.h"
#include "Timer.h"
#include "TileFunctions.h"
#include <iostream>
Bomb::Bomb(int power, float fuse, Vec2f& pos,SpriteSheet& ssr,int ownership)
{
    power_=power;
    fuse_=fuse;
    bombSprite_.SetPos(Settle(pos));
    std::cout<<Settle(pos).x<<" "<<Settle(pos).y<<"\n";
    bombSprite_.AssignImage(ssr);
    bombSprite_.Init(fuse/3);
    owner_=ownership;
}

void Bomb::Draw()
{
    bombSprite_.Draw();
}

Vec2f Bomb::GetPos()const
{
    return bombSprite_.GetPos();
}

void Bomb::Update()
{
    fuse_-=TheTimer::Instance()->GetDt();
    bombSprite_.Update();
}

bool Bomb::HasExploded()const
{
    return(fuse_<=0);
}

int Bomb::GetTag()const
{
    return owner_;
}

int Bomb::GetPower()const
{
    return power_;
}