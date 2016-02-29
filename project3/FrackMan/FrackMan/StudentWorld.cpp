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
    updateDisplayText();
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

bool StudentWorld::tellThisActorTodoSomething(Actor* actor){
    actor->doSomething();
}

bool StudentWorld::theplayerDiedDuringThisTick(){
    return !m_frackman->isAlive();
}

bool StudentWorld::theplayerCompleteTheCurrentLevel(){
    return m_frackman->hasBarrels() == m_//TODO
}

void StudentWorld::setDisplayText(){
    int score = getCurrentScore();
    int level = getCurrentGameLevel();
    int lives = getNumLivesLeft();
    int health = getCurrentHealth();
    int squirts = getSquirtsLeftInSquirtGun();
    int gold = getPlayerGoldCount();
    int sonar = getPlayerSonarChargeCount();
    int barrelsLeft = getNumberOfBarrelsRemainingToBePickedUp();
    
    char stat[500];
    sprintf(stat, "Scr:%08d  Lvl:%2d  Lives: %01d  Hlth: %3d%%  Water: %2d  Gld: %2d  Sonar: %2d  Oil Left:%2d", score, level, lives, health, squirts, gold, sonar, bareelsLeft);
    string s = string(stat);
    setGameStatText(s);
}
 */
