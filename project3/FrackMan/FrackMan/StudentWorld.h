#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
const int DIRTS_WIDTH = VIEW_WIDTH - SPRITE_WIDTH;
const int DIRTS_HEIGHT = VIEW_HEIGHT - SPRITE_HEIGHT;
class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init()
	{
        //Initialize m_actors, but this is not needed for Part1
        //Initialize m_frackman
        
        
        //Initialize m_dirts
        
        //for(int i = 0; i < DIRTS_WIDTH; i++)
            //
        //for(int j = 0; j < DIRTS_HEIGHT; j++)
          //      m_dirts[i][j] = new Dirt(i, j);
        //playSound();
    
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp()
	{
	}

private:
    std::vector<Actor*> m_actors;
    //FrackMan* m_frackman;
    Dirt* m_dirts[DIRTS_WIDTH][DIRTS_HEIGHT];
    
};

#endif // STUDENTWORLD_H_
