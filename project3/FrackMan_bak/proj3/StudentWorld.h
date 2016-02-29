#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    enum ITEM_NAME{GOLD, WATER, BARREL, SONAR};
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
    
    bool isDirtVisible(int x, int y) const { return !m_dirts[x][y]->isDead(); }
    void setDirtInVisible(int x, int y) {
        m_dirts[x][y]->setVisible(false);
        m_dirts[x][y]->setStatus(Dirt::DEAD);
    }
    //Dirt* getDirt(int x, int y) const { return m_dirts[x][y]; }//TODO
    
    void increaseInventory(ITEM_NAME itme_name, int howMuch);
    //void decreaseInventory(string itme_name, unsigned int howMuch);
    bool isplayerAround(int x, int y, double R);
    
    //bool isEnvItem(int x , int y) const; // Boulder and visible dirt
    //bool isPeople(int x, int y) const{ return false;} // Protesters and Frackman
   // bool isPickableItem(int x, int y) const{ return false; } // Kit, oil, nugget, pool, squirt?
    void playerDoSomething() { m_frackman->doSomething(); }
    //Frackman* getPlayer() const { return m_frackman; }
    
    bool theplayerDied() const { return m_frackman->getCurrentHealth() <= 0? true:false; }
    bool theplayerCompletedTheCurrentLevel() const { return m_frackman->getNumberOfBarrelsRemainingToBePickedUp() == 0; }
    
    bool occupiedByBoulderRadius(int x, int y, double R);
    bool occupiedByDirt(int x, int y, int sz);
    bool occupiedByBoulder(int x, int y, int sz);
    
    void addActor(Actor* ac) { m_vec_actors.push_back(ac); }

    void removeDeadActors();
    void setVisibleInRadius(int x, int y, double R);
    bool occupiedByAgent(int x, int y, int size);
    
    //TODO
    int getPlayerX() { return m_frackman->getX(); }
    int getPlayerY() { return m_frackman->getY(); }
    
    void getFrackmanAnnoyed(int damage);
    
    //TODO
    bool clearDirtInStraightLine(int sx, int sy, int ex, int ey, int size);
    
private:
    void actorDoSomething(Actor* ac){ ac->doSomething(); }
    void setDisplayText();
    void populateBoulders();
    void populateGoldNuggets();
    void populateBarrels();
    void populateRegularProtester();
    void addObjects();
    void addProtester() {}
    void populateSonar();
    void populateWater() {}
    bool occupiedByItemInRadius(int x, int y, double R);
    bool occupiedByItem(int x, int y, int sz);
    bool inTheShaft(int x, int y) { return (x>= 26 && x <=33 && y >=0 && y <=56); }
    Dirt* m_dirts[VIEW_WIDTH][VIEW_HEIGHT];
    Frackman* m_frackman;
    int m_lastprotestercount;
    int m_numprotester;
    std::vector<Actor*> m_vec_actors;
    std::vector<Actor*> m_vec_items;
};

#endif // STUDENTWORLD_H_
