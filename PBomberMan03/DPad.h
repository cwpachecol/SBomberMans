#ifndef DPAD_H_INCLUDED
#define DPAD_H_INCLUDED

#include <vector>
#include "LoadState.h"
class DPad
{
public:
    DPad();
    bool LevelDown();
    bool LevelUp();
    bool PlayersUp();
    bool PlayersDown();

    int GetPlayerNum()const;
    int GetLevel()const;
    void Draw();
private:
    int currentLevel;
    int currentPlayerNum;
};

#endif