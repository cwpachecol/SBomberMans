#ifndef LOADSTATE_H_INCLUDED
#define LOADSTATE_H_INCLUDED

#include "GameState.h"
#include "Singleton.h"
#include "NonCopyable.h"
#include "TTFont.h"
#include "Image.h"
#include "SpriteSheet.h"
#include <vector>
#include "TextButton.h"
#include "Button.h"

class LoadState;
typedef Singleton<LoadState> TheLoadState;

enum PLAYER_ORDER{PLAYER_WHITE=0,PLAYER_BLACK,PLAYER_RED,PLAYER_BLUE,PLAYER_NINJA};
class LoadState:public GameState
{
public:
    ~LoadState();
    virtual void OnActive();
    virtual void OnInactive();
    virtual void Update();
    virtual void Draw();
    void ReadLevels();
private:
    LoadState();
    friend TheLoadState;
    bool isLoaded;
public:
    Image gameboyBG,
        gameboyScreen,
        gameboyScreenGrid,
        gameboyWinScreen;

    SpriteSheet menuResetBomb,
        menuPlayBomb,
        menuBombExplosion,
        rArrow,lArrow,uArrow,dArrow;

    SpriteSheet bomb,
        explosion,
        wall;

    Button upArrowButton,
        downArrowButton,
        leftArrowButton,
        rightArrowButton;

    TextButton startButton,
        resetButton;

    std::vector<std::string> musicTracks;
    std::string 
        mChunkClick,
        mChunkGameStart,
        mChunkPause,
        mChunkPlayerDeath,
        mChunkReset,
        mChunkSetBomb,
        mChunkExplode,
        mChunkTransition;

    TTFont pixelFont;
    SDL_Colour RedColor,
        BlueColor,
        OrangeColor,
        YellowColor,
        GreenColor,
        WhiteColor,
        BlackColor,
        PinkColor;

    std::vector<std::string> buttonText;
    std::vector<Vec2f> buttonBuild;
    std::vector<std::string> levelNames;

    std::vector<std::vector<Vec2f>> mapBuild;
    std::vector<std::vector<bool>> mapBuildBreakables;
    std::vector<std::vector<Vec2f>> spawnPoints;

    std::vector<SpriteSheet> playerSprites;

    std::vector<std::string> playerShouts;
    std::vector<int> bombPowers;
    std::vector<int> playerMaxBomb;
    std::vector<float> bombFuseTime;
    std::vector<float> playerMoveSpeed;
    std::vector<float> explosionDuration;

    int wallScore,
        playerScore,
        playerSuicideScore;
};




#endif