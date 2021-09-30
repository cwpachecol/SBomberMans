#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "Image.h"
#include "Vec2.h"

class SpriteSheet:private Image
{
public:
    SpriteSheet();
    SpriteSheet(const std::string& filename, int numCellsInX,int numCellsInY);
    bool Load(const std::string& filename, int numCellsInX,int numCellsInY);
    void Draw(int x,int y,int frame);
    int GetTotalFrames();
    Vec2<int> GetCellSize();
private:
    int m_totalFrameNum;
    int m_cellHeight;
    int m_cellWidth;
    int m_numCellsInX;
    int m_numCellsInY;
};

#endif