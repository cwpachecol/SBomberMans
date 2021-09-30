#ifndef WALLMANAGER_H_INCLUDED
#define WALLMANAGER_H_INCLUDED

#include "Singleton.h"
#include "NonCopyable.h"
#include <list>
#include "Wall.h"

class WallManager;
typedef Singleton<WallManager> TheWallManager;

class WallManager:public NonCopyable
{
public:
    ~WallManager();
    void Init(int);
    void Update();
    void Draw();
    void Reset();
    int ExplosionWallCheck(Vec2f pos,int tag);
    bool PlayerWallCheck(Vec2f pos,int tag);
    bool PlayerWallCheck(AABB2D& box,int tag);
private:
    WallManager();
    friend TheWallManager;
    std::list<Wall> walls_;

};

#endif