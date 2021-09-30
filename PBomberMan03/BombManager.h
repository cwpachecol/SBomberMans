#ifndef BOMBMANAGER_H_INCLUDED
#define BOMBMANAGER_H_INCLUDED
#include "Bomb.h"
#include "NonCopyable.h"
#include "Singleton.h"
#include <list>
class BombManager;
typedef Singleton<BombManager> TheBombManager;

class BombManager:public NonCopyable
{
public:
    bool SetBomb(int power, float fuse, Vec2f Pos,int owner);
    void Update();
    void Draw();
    void Load();
    void Reset();
private:
    BombManager();
    friend TheBombManager;
    SpriteSheet* bombSheet_;
    std::list<Bomb> bombQueue_;
};

#endif