#include "SpriteSheet.h"
#include "Screen.h"
#include <assert.h>

SpriteSheet::SpriteSheet()
{
    m_totalFrameNum=1;
    m_numCellsInX=1;
    m_numCellsInY=1;
    m_cellWidth=0;
    m_cellHeight=0;
}

SpriteSheet::SpriteSheet(const std::string& filename, int cellNumInX,int cellNumInY)
{
    m_numCellsInX=cellNumInX;
    m_numCellsInY=cellNumInY;

    //load the base image
    assert(Image::Load(filename));
    m_cellWidth= Image::m_imageLoc->w/m_numCellsInX;
    m_cellHeight= Image::m_imageLoc->h/m_numCellsInY;
    m_totalFrameNum = m_numCellsInX*m_numCellsInY;
}

void SpriteSheet::Draw(int x,int y, int cellNum)
{
    assert(Image::m_imageLoc);//image hasnt been loaded sucessfully
    //find top left coord
    int cellXPos = (cellNum % m_numCellsInX) *m_cellWidth;
    int cellYPos = (cellNum / m_numCellsInX) *m_cellHeight;

    //draw the cell
    SDL_Rect r= {x,y,0,0};
    SDL_Rect crop={cellXPos,cellYPos,m_cellWidth,m_cellHeight};
    SDL_BlitSurface(m_imageLoc, &crop, TheScreen::Instance()->GetScreen(), &r);
}

bool SpriteSheet::Load(const std::string& filename, int cellNumInX, int cellNumInY)
{
    //initilize cell nums
    m_numCellsInX=cellNumInX;
    m_numCellsInY=cellNumInY;

    //load the base image
    if(!Image::Load(filename))
    {
        return false;
    }
    m_cellWidth= Image::m_imageLoc->w/m_numCellsInX;
    m_cellHeight= Image::m_imageLoc->h/m_numCellsInY;
    m_totalFrameNum = m_numCellsInX*m_numCellsInY;
    return (Image::m_imageLoc !=0);
}

int SpriteSheet::GetTotalFrames()
{
    return m_totalFrameNum;
}

Vec2<int> SpriteSheet::GetCellSize()
{
    Vec2<int> myVec(m_cellWidth,m_cellHeight);
    return myVec;
};