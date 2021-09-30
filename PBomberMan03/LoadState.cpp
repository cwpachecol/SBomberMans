#include "LoadState.h"
#include "Game.h"
#include "MenuState.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

LoadState::~LoadState()
{

}
LoadState::LoadState()
{
    bool isLoaded=false;
    srand((unsigned int)time(0));
}

void LoadState::OnActive()
{
    if(isLoaded)
    {
        TheGame::Instance()->SetState(TheMenuState::Instance());
    }
    else
    {

        gameboyBG.Load("GameBoyBackground.jpg");
        gameboyScreenGrid.Load("TileFilter.png");
        gameboyScreen.Load("GrassBackground.png");
        gameboyWinScreen.Load("WinBanner.png");

        menuResetBomb.Load("MenuResetButton.png",3,1);
        menuPlayBomb.Load("MenuPlayButton.png",3,1);
        menuBombExplosion.Load("MenuExplosion.png",4,1);
        rArrow.Load("RightArrow.png",3,1);
        lArrow.Load("LeftArrow.png",3,1);
        uArrow.Load("UpArrow.png",3,1);
        dArrow.Load("DownArrow.png",3,1);

        musicTracks.push_back("Music/BadSeed(8Bit).mp3");
        musicTracks.push_back("Music/Crusade(8Bit).mp3");
        musicTracks.push_back("Music/CrusadeFinal(8Bit).mp3");
        musicTracks.push_back("Music/Giggle(8Bit).mp3");
        musicTracks.push_back("Music/Polka(8Bit).mp3");
        musicTracks.push_back("Music/Tom Jones - Sex bomb.mp3");

        playerShouts.push_back("SoundEffects/WhiteBomberMan.wav");
        playerShouts.push_back("SoundEffects/BlackBomberMan.wav");
        playerShouts.push_back("SoundEffects/RedBomberMan.wav");
        playerShouts.push_back("SoundEffects/BlueBomberMan.wav");

        mChunkClick="SoundEffects/Click.wav";
        mChunkGameStart="SoundEffects/GameStart.wav";
        mChunkPause="SoundEffects/Pause.wav";
        mChunkPlayerDeath="SoundEffects/PlayerDeath.wav";
        mChunkReset="SoundEffects/Reset.wav";
        mChunkSetBomb="SoundEffects/SetBomb.wav";
        mChunkExplode="SoundEffects/BombMedium.wav";
        mChunkTransition="SoundEffects/Transition.wav";

        SDL_Colour Orange={255,165,0};
        OrangeColor=Orange;
        SDL_Colour Red={255,0,0};
        RedColor=Red;
        SDL_Colour Blue={0,0,255};
        BlueColor=Blue;
        SDL_Colour Green={0,255,0};
        GreenColor=Green;
        SDL_Colour White={255,255,255};
        WhiteColor=White;
        SDL_Colour Black={0,0,0};
        BlackColor=Black;
        SDL_Colour Pink={250,128,114};
        PinkColor=Pink;

        mapBuild;
        mapBuildBreakables;
        upArrowButton=Button(uArrow,0,Vec2f(53,60));
        downArrowButton=Button(dArrow,1,Vec2f(53,110));
        rightArrowButton=Button(rArrow,2,Vec2f(80,88));
        leftArrowButton=Button(lArrow,3,Vec2f(20,88));
        startButton=TextButton(menuPlayBomb,4,Vec2f(180,78),"Play",Vec2f(16,30),BlackColor,pixelFont);
        resetButton=TextButton(menuResetBomb,6,Vec2f(247,43),"Reset",Vec2f(12,30),RedColor,pixelFont);

        bomb.Load("Bomb.png",3,1);
        explosion.Load("Explosion.png",4,7);
        wall.Load("Walls.png",2,1);
        pixelFont.Load("vgasys.fon",12);

        ReadLevels();

        wallScore=10;
        playerScore=100;
        playerSuicideScore=-100;

        playerSprites.resize(4);
        playerSprites[PLAYER_WHITE].Load("BomberWhite.png",3,4);
        playerSprites[PLAYER_BLACK].Load("BomberBlack.png",3,4);
        playerSprites[PLAYER_RED].Load("BomberRed.png",3,4);
        playerSprites[PLAYER_BLUE].Load("BomberBlue.png",3,4);
        //1
        bombPowers.resize(4);
        bombPowers[PLAYER_WHITE]=1;
        bombPowers[PLAYER_BLACK]=1;
        bombPowers[PLAYER_RED]=1;
        bombPowers[PLAYER_BLUE]=1;
        //1
        playerMaxBomb.resize(4);
        playerMaxBomb[PLAYER_WHITE]=1;
        playerMaxBomb[PLAYER_BLACK]=1;
        playerMaxBomb[PLAYER_RED]=1;
        playerMaxBomb[PLAYER_BLUE]=1;
        //3
        bombFuseTime.resize(4);
        bombFuseTime[PLAYER_WHITE]=3;
        bombFuseTime[PLAYER_BLACK]=3;
        bombFuseTime[PLAYER_RED]=3;
        bombFuseTime[PLAYER_BLUE]=3;
        //55
        playerMoveSpeed.resize(4);
        playerMoveSpeed[PLAYER_WHITE]=55.0f;
        playerMoveSpeed[PLAYER_BLACK]=55.0f;
        playerMoveSpeed[PLAYER_RED]=55.0f;
        playerMoveSpeed[PLAYER_BLUE]=55.0f;
        //0.8
        explosionDuration.resize(4);
        explosionDuration[PLAYER_WHITE]=0.8f;
        explosionDuration[PLAYER_BLACK]=0.8f;
        explosionDuration[PLAYER_RED]=0.8f;
        explosionDuration[PLAYER_BLUE]=0.8f;


        isLoaded=true;
    }
}

void LoadState::OnInactive()
{}

void LoadState::Update()
{
    if(isLoaded)
    {
        TheGame::Instance()->SetState(TheMenuState::Instance());
    }

}

void LoadState::Draw()
{

}

void LoadState::ReadLevels()
{
    int level=0;
    Vec2f screenOrigin(60,45);
    int increment =20;
    std::string data;
    std::fstream read;
    read.open("Levels.txt");
    assert(read);
    std::vector<Vec2f> locations;
    std::vector<bool> props;
    int line=0;
    bool readingMap=false;
    while(read.good())
    {
        std::getline(read,data);
        int dataLength=data.length();
        for(int i=0;i<dataLength;++i)
        {
            if(data[i]=='$')
            {
                break;
            }
            if(data[i]=='<')
            {
                int j=i+1;
                std::string temp;
                while(data[j]!='>')
                {
                    temp.push_back(data[j]);
                    ++j;
                }
                int lvl=atoi(temp.c_str());
                mapBuild.resize(lvl);
                mapBuildBreakables.resize(lvl);
                spawnPoints.resize(lvl);
                for(int k=0;k<lvl;++k)
                {
                    spawnPoints[k].resize(4);
                }
                i=j;
            }
            if(data[i]==' ')
            {
                continue;
            }
            if(data[i]=='#')
            {
                int j=i+1;
                std::string temp;
                while(data[j]!='#')
                {
                    temp.push_back(data[j]);
                    ++j;
                }
                levelNames.push_back(temp);
                i=j;
            }
            if(data[i]=='{')
            {
                readingMap=true;
                line=-1;
                break;
            }
            if(data[i]=='}')
            {

                readingMap=false;
                mapBuild[level]=locations;
                mapBuildBreakables[level]=props;
                locations.clear();
                props.clear();
                ++level;
            }
            if(readingMap)
            {
                if(data[i]=='1'||data[i]=='2')
                {
                    locations.push_back(Vec2f(screenOrigin.x+increment*i,
                        screenOrigin.y+line*increment));
                    if(data[i]=='1')
                    {
                        props.push_back(true);
                    }
                    else
                    {
                        props.push_back(false);
                    }
                }
                else if(data[i]=='W')
                {
                    spawnPoints[level][PLAYER_WHITE]=Vec2f(screenOrigin.x+increment*i,
                        screenOrigin.y+line*increment);
                    continue;
                }
                else if(data[i]=='Z')
                {
                    spawnPoints[level][PLAYER_BLACK]=Vec2f(screenOrigin.x+increment*i,
                        screenOrigin.y+line*increment);
                    continue;
                }
                else if(data[i]=='R')
                {
                    spawnPoints[level][PLAYER_RED]=Vec2f(screenOrigin.x+increment*i,
                        screenOrigin.y+line*increment);
                    continue;
                }
                else if(data[i]=='B')
                {
                    spawnPoints[level][PLAYER_BLUE]=Vec2f(screenOrigin.x+increment*i,
                        screenOrigin.y+line*increment);
                    continue;
                }
            }
        }
        line++;
    }
}