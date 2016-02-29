#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
int StudentWorld::init(){
    //Initialize Frackman
    m_frackman = new Frackman(this);
    m_frackman->setVisible(true);
    m_vec_actors.push_back(m_frackman);
    //Initialize dirts
    for(int i = 0; i < VIEW_WIDTH; i++){
        for(int j = 0; j < VIEW_HEIGHT; j++){
            m_dirts[i][j] = new Dirt(this, i, j);
            m_dirts[i][j]->setVisible(true);
            if(i >= (VIEW_WIDTH-SPRITE_WIDTH)/2 && i < (VIEW_WIDTH+SPRITE_WIDTH)/2 && j >= SPRITE_HEIGHT )
                m_dirts[i][j]->setVisible(false);
            if(j >= VIEW_HEIGHT - SPRITE_HEIGHT)
                m_dirts[i][j]->setVisible(false);
        }
    }
    //playSound(SOUND_NONE);//TODO
    m_vec_actors.push_back(new Boulder(this, 25, 25));
    //m_vec_actors.push_back(new Boulder(this, 45, 45));
    m_vec_actors[1]->setVisible(true);
    //m_vec_actors[2]->setVisible(true);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
    
    setDisplayText();
    if(theplayerDied()){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    //playerDoSomething();
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        if((*it)->getStatus() != Actor::DEAD){
            //if(isEnvItem((*it)->getX(), (*it)->getY()))
                //printf("status: %d", (*it)->getStatus());
            actorDoSomething(*it);
            
            if(theplayerDied()){
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            
            //if(theplayerCompletedTheCurrentLevel())
                //return GWSTATUS_FINISHED_LEVEL;
        }
    }
    
    removeDeadActors();
    
    if(theplayerDied()){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    //if(theplayerCompletedTheCurrentLevel()){
        //playSound(SOUND_FINISHED_LEVEL);
        //return GWSTATUS_FINISHED_LEVEL;
    //}
    //actorDoSomething();
    //getPlayer()->doSomething();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    for(int i = 0; i < VIEW_WIDTH; i++)
        for(int j = 0; j < VIEW_HEIGHT; j++)
            delete m_dirts[i][j];
    
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end();){
        delete *it;
        it = m_vec_actors.erase(it);
    }
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
    
    char stat[1000];
    sprintf(stat, "Scr:  %06d  Lvl:%2d  Lives: %01d  Hlth: %3d%%  Water: %2d  Gld: %2d  Sonar: %2d  Oil Left:%2d", score, level, lives, health, squirts, gold, sonar, barrelsLeft);
    string s = string(stat);
    setGameStatText(s);
}

bool StudentWorld::isEnvItem(int x, int y) const{
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++)
        if (((*it)->getID() == IID_BOULDER || (*it)->getID() == IID_DIRT) && ((*it)->getX() == x && (*it)->getY() == y))
            return true;
    return false;
}

void StudentWorld::removeDeadActors(){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); ){
        if((*it)->getStatus() == Actor::DEAD){
            it = m_vec_actors.erase(it);
            (*it)->setVisible(false);
        }
        else
            it++;
    }
}