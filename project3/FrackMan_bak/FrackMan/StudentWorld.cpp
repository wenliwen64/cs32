#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

/*
int StudentWorld::move(){
    setDisplayText();
    for(auto it = m_actors.begin(); it != m_actors.end(); it++){
        if(*it->isAlive()){
            tellThisActorTodoSomething(*it)；
            
            if(theplayerDiedDuringThisTick())
                return GWSTATUS_PLAYER_DIED;
            if(theplayerCompleteTheCurrentLevel())
                return GWSTATUS_FINISHED_LEVEL;
        }
    }
    
    removeDeadGameObjects();
    
    if(theplayerDiedDuringThisTick())
        return GWSTATUS_PLAYER_DIED;
    
    if(theplayerCompletedTheCurrentLevel()){
        playFinishedLevelSound();
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}
*/
     
void StudentWorld::setDisplayText(){
    int score = getCurrentScore();
    int level = getCurrentGameLevel();
    int lives = getNumLivesLeft();
    int health = getCurrentHealth();
    int squirts = getSquirtsLeftInSquirtGun();
    int gold = getPlayerGoldCount();
    int sonar = getPlayerSonarChargeCount();
    int barrelsLeft = getNumberOfBarrelsRemainingToBePickedUp();
    
    char stat[1000];
    sprintf(stat, "Scr:%08d  Lvl:%2d  Lives: %01d  Hlth: %3d%%  Water: %2d  Gld: %2d  Sonar: %2d  Oil Left:%2d", score, level, lives, health, squirts, gold, sonar, barrelsLeft);
    //sprintf(stat, "Scr:%08d  Lvl:%2d  Lives: %01d  Hlth: %3d%%  Water: %2d  Gld: %2d  Sonar: %2d  Oil Left:%2d", 100, 1, 1, 3, 5, 0, 0, 1);
    //sprintf(stat, "Scr:%08d  Lvl:%2d  Lives: %01d  Hlth: %3d%%  Water: %2d  Gld: %2d  Sonar: %2d  Oil Left:%2d", score, level, lives, 3, 5, 0, 0, 1);
    string s = string(stat);
    setGameStatText(s);
}