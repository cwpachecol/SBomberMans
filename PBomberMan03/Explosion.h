#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED
#include "Sprite.h"
#include <vector>
#include "Vec2.h"
class Explosion
{
public:
    void Update();
    void Draw();
    void Explode(Vec2f pos, int power, int tag, SpriteSheet& sse);
    bool HasFinished()const;
    AABB2D GetHozHitbox()const;
    AABB2D GetVertHitbox()const;
    int GetTag()const;
private:
    Vec2f centerPos_;
    float explosionDuration_;
    bool hasFinished_;
    std::vector<Sprite> sprites_;
    AABB2D horizontalHitbox_;
    AABB2D verticalHitbox_;
    bool shortUp_;
    bool shortLeft_;
    bool shortRight_;
    bool shortDown_;
    int tag_;

};

#endif