#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

    virtual int init();

    virtual int move();

    virtual void cleanUp();


    int getCurrentScore() const{ return getScore(); }
    int getCurrentGameLevel() const { return getLevel(); }
    int getNumLivesLeft() const { return getLives(); }
    int getCurrentHealth() const { return m_frackman->getCurrentHealth(); }
    int getSquirtsLeftInSquirtGun() const { return m_frackman->getSquirtsLeftInSquirtGun(); }
    int getPlayerGoldCount() const { return m_frackman->getGoldCount(); }
    int getPlayerSonarChargeCount() const { return m_frackman->getSonarChargeCount(); }
    int getNumberOfBarrelsRemainingToBePickedUp() const { return m_frackman->getNumberOfBarrelsRemainingToBePickedUp(); }
    bool isDirtVisible(int x, int y) const { return m_dirts[x][y]->isVisible(); }
    void setDirtVisible(int x, int y, bool status) { m_dirts[x][y]->setVisible(status); }
    //Dirt* getDirt(int x, int y) const { return m_dirts[x][y]; }//TODO
    bool isEnvItem(int x , int y) const; // Boulder and visible dirt
    bool isPeople(int x, int y) const{ return false;} // Protesters and Frackman
    bool isPickableItem(int x, int y) const{ return false; } // Kit, oil, nugget, pool, squirt?
    void actorDoSomething(Actor* ac){ ac->doSomething(); }
    //void playerDoSomething() { m_frackman->doSomething(); }
    //Frackman* getPlayer() const { return m_frackman; }
    
    bool theplayerDied() const { return m_frackman->getCurrentHealth() <= 0? true:false; }
    bool theplayerCompletedTheCurrentLevel() const { return m_frackman->getNumberOfBarrelsRemainingToBePickedUp() == 0; }
    void removeDeadActors();
    
private:
    void setDisplayText();
    Dirt* m_dirts[VIEW_WIDTH][VIEW_HEIGHT];
    Frackman* m_frackman;
    std::vector<Actor*> m_vec_actors;
};

#endif // STUDENTWORLD_H_
