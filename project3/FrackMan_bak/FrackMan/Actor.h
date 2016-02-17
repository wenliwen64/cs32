#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0):GraphObject(imageID, startX, startY, dir, size, depth), m_sw(sw){}
    virtual ~Actor(){}
    virtual void doSomething() = 0;
    StudentWorld* getWorld(){ return m_sw; }
private:
    StudentWorld* m_sw;
    
};

class Dirt : public Actor{
public:
    Dirt(StudentWorld* sw, int startX, int startY):Actor(sw, IID_DIRT, startX, startY, right, 0.25, 3){}
    virtual ~Dirt(){}
    virtual void doSomething(){}
 
};

class Frackman : public Actor{
public:
    Frackman(StudentWorld* sw):Actor(sw, IID_PLAYER, 30, 60, right, 1, 0), m_hit(100), m_squirts(5), m_sonar(1), m_goldCounts(0), m_barrels(0){}
    virtual ~Frackman(){}
    virtual void doSomething();
    void setHealth(int h) { m_hit = h; }
    void setSquirtsLeftInSquirtGun(int s) {m_squirts = s; }
    void setGoldCount(int g) { m_goldCounts = g; }
    void setSonarChargeCount(int s) { m_sonar = s; }
    void setNumberOfBarrelsRemainingToBePickedUp(int b) { m_barrels = b; }
    int getCurrentHealth() const { return m_hit; }
    int getSquirtsLeftInSquirtGun() const { return m_squirts; }
    int getGoldCount() const { return m_goldCounts; }
    int getSonarChargeCount() const { return m_sonar; }
    int getNumberOfBarrelsRemainingToBePickedUp() const { return m_barrels; }
    
private:
    int m_hit;
    int m_squirts;
    int m_sonar;
    int m_goldCounts;
    int m_barrels;
};

class Squirt : public Actor{
public:
    Squirt(StudentWorld):Actor(){}
private:
    Frackman* m_frackman;
    
};
#endif // ACTOR_H_
