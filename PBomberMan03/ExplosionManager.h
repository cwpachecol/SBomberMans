#ifndef EXPLOSIONMANAGER_H_INCLUDED
#define EXPLOSIONMANAGER_H_INCLUDED

#include "Singleton.h"
#include "NonCopyable.h"
#include <deque>
#include "Explosion.h"
#include "AABB2D.h"
class ExplosionManager;
typedef Singleton<ExplosionManager> TheExplosionManager;

class ExplosionManager:public NonCopyable
{
public:
    void Update();
    void Draw();
    void Init();
    void SpawnExplosion(Vec2f pos,int power, int tag);
    int CheckCollision(AABB2D box);
    void Reset();
private:
    std::deque<Explosion> currentExplosions_;
    ExplosionManager();
    friend TheExplosionManager;
    SpriteSheet* explosion_;
};
#endif