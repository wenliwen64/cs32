#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init()
	{
        //Initialize Frackman
        m_frackman = new Frackman(this);
        m_frackman->setVisible(true);
        //Initialize dirts
        for(int i = 0; i < 64; i++){
            for(int j = 0; j < 64; j++){
                m_dirts[i][j] = new Dirt(this, i, j);
                m_dirts[i][j]->setVisible(true);
                if(i > 29 && i < 34 && j > 3 )
                    m_dirts[i][j]->setVisible(false);
                if(j >= 60)
                    m_dirts[i][j]->setVisible(false);
            }
        }
        //playSound(SOUND_NONE);//TODO
		return GWSTATUS_CONTINUE_GAME;
	}

    virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		//decLives();
		//return GWSTATUS_PLAYER_DIED;
        setDisplayText();
        if(theplayerDied()){
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        getPlayer()->doSomething();
        return GWSTATUS_CONTINUE_GAME;
    }

	virtual void cleanUp()
	{
        for(int i = 0; i < 64; i++)
            for(int j = 0; j < 64; j++)
                delete m_dirts[i][j];
        
        delete m_frackman;
	}
    

    int getCurrentScore() const{ return getScore(); }
    int getCurrentGameLevel() const { return getLevel(); }
    int getNumLivesLeft() const { return getLives(); }
    int getCurrentHealth() const { return m_frackman->getCurrentHealth(); }
    int getSquirtsLeftInSquirtGun() const {return m_frackman->getSquirtsLeftInSquirtGun(); }
    int getPlayerGoldCount() const { return m_frackman->getGoldCount(); }
    int getPlayerSonarChargeCount() const { return m_frackman->getSonarChargeCount(); }
    int getNumberOfBarrelsRemainingToBePickedUp() const { return m_frackman->getNumberOfBarrelsRemainingToBePickedUp(); }
    Dirt* getDirt(int x, int y) const { return m_dirts[x][y]; }
    Frackman* getPlayer() const { return m_frackman; }
    
    bool theplayerDied() const { return getPlayer()->getCurrentHealth() <= 0? true:false; }
    
private:
    void setDisplayText();
    Dirt* m_dirts[64][64];
    Frackman* m_frackman;
};

#endif // STUDENTWORLD_H_
