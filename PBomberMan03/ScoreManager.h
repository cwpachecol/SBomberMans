#ifndef SCOREMANAGER_H_INCLUDED
#define SCOREMANAGER_H_INCLUDED
#include "Singleton.h"
#include "NonCopyable.h"
#include <vector>
#include "Vec2.h"

class ScoreManager;
typedef Singleton<ScoreManager> TheScoreManager;
class ScoreManager:public NonCopyable
{
public:
    void Draw();
    void Init(int playerNum);
    void SetPos(Vec2f pos);
    void SetSeperation(int seperation);
    void AddScore(int score, int tag);
    void MinusScore(int score,int tag);
    int GetScore( int tag);
    int GetHighestScore();
    void Reset();
    void SetMaxMapScore(int maxScore);
private:
    Vec2f pos_;
    int maxMapScore_;
    int seperation;
    ScoreManager();
    int numOfPlayers;
    friend TheScoreManager;
    std::vector<int> scores_;
};
#endif