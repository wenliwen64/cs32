#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
//#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0, bool blockable = false, bool pickUpAbleByFrackman = false, bool pickUpAbleByProtester = false, bool canpickthingsup = false) : GraphObject(imageID, startX, startY, dir, size, depth), m_sw(sw), m_blockable(blockable), m_pickupablebyfrackman(pickUpAbleByFrackman), m_pickupablebyprotester(pickUpAbleByProtester){}
    virtual ~Actor(){}
    virtual void doSomething() = 0;
    StudentWorld* getWorld(){ return m_sw; }
    bool inRadius(int x, int y, double R);
    //virtual void setStatus() = 0; hard to determine the return type
    virtual bool isDead() = 0;// TODO
    virtual bool isBlockable() { return m_blockable; }
    virtual bool isPickUpAbleByFrackman() { return m_pickupablebyfrackman; }
    virtual bool isPickUpAbleByProtester() { return m_pickupablebyprotester; }
    virtual bool canPickThingsUp() { return m_canpickthingsup; }
private:
    StudentWorld* m_sw;
    bool m_blockable;
    bool m_pickupablebyfrackman;
    bool m_pickupablebyprotester;
    bool m_canpickthingsup;
    
};

inline bool Actor::inRadius(int x, int y, double R){
    return sqrt((getX() - x) * (getX() - x) + (getY() - y) * (getY() - y)) <= R? true:false;
}

// Class People
class People : public Actor{
public:
    enum STATUS {ALIVE, LEAVE, ANNOYED, DEAD};
    People(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size = 1.0, unsigned int depth = 0, bool blockable = false, bool pickUpAbleByFrackman = false, bool pickUpAbleByProtester = false, bool canPickThingsUp = true ) : Actor(sw, imageID, startX, startY, dir, size, depth, blockable, pickUpAbleByFrackman, pickUpAbleByProtester, canPickThingsUp){}
    virtual ~People() {}
    virtual void setDead() { m_status = DEAD; }
    virtual bool isDead() { return m_status == DEAD; }
private:
    int m_hit;
    STATUS m_status;
};

// Class Protester

class Protester : public People{
public:
    Protester(StudentWorld* sw, int imageID, int wait_ticks) : People(sw, imageID, VIEW_WIDTH-SPRITE_WIDTH, VIEW_HEIGHT-SPRITE_HEIGHT, left), m_tickstowaitbetweenmoves(wait_ticks), m_rest(false), m_rest_ticks(0), m_leaving(false), m_shout_count(0), m_last_shout_ticks_lapsed(100), m_num_squares_to_move_in_current_direction(8+rand()%53), m_perp_turn_ticks_count(1000){ }
    virtual ~Protester(){}
    virtual void doSomething();
    bool inRest() const { return m_rest_ticks % m_tickstowaitbetweenmoves == 0? false:true; }
    bool isLeaving() const { return m_leaving; }
    //virtual void annoy(int damage) = 0;
    virtual bool seeAndFaceToPlayer();
    virtual bool shoutInLastNonRestingTicks();
    virtual bool alignWithFrackman();
    virtual bool awayFromFrackman();
private:
    bool atExit() { return (getX() == 60 && getY() == 60); }
    GraphObject::Direction towardFrackmanDirection();
    void setNumSquaresToMoveInCurrentDirection(int ns){ m_num_squares_to_move_in_current_direction = ns; }
    int getNumSquaresToMoveInCurrentDirection() { return m_num_squares_to_move_in_current_direction; }
    int generateNumSquaresToMoveInCurrentDirection() { return 8 + rand() % 53; }
    Direction getTurnDirection();
    bool atIntersection();
    int m_tickstowaitbetweenmoves;
    bool m_rest;
    int m_rest_ticks;
    bool m_leaving;
    int m_shout_count;
    char m_maze[64][64];
    int m_last_shout_ticks_lapsed;
    int m_num_squares_to_move_in_current_direction;
    int m_perp_turn_ticks_count;
};

// Class Frackman
class Frackman : public Actor{
public:
    enum STATUS{ALIVE, DEAD};
    Frackman(StudentWorld* sw):Actor(sw, IID_PLAYER, 30, 60, right, 1, 0, false, false, false, true), m_hit(10), m_squirts(5), m_sonar(1), m_goldCounts(0), m_barrels(0){}
    virtual ~Frackman(){}
    virtual void doSomething();
    void setHealth(int h) { m_hit = h; }
    void decreaseHealth(int howMuch) { m_hit -= howMuch; }
    void increaseSquirtsLeftInSquirtGun(int s) { m_squirts += s; }
    void increaseGoldCount(int g) { m_goldCounts += g; }
    void increaseSonarChargeCount(int s) { m_sonar += s; }
    void increaseNumberOfBarrelsRemainingToBePickedUp(int b) { m_barrels += b; }
    int getCurrentHealth() const { return m_hit; }
    int getSquirtsLeftInSquirtGun() const { return m_squirts; }
    int getGoldCount() const { return m_goldCounts; }
    int getSonarChargeCount() const { return m_sonar; }
    int getNumberOfBarrelsRemainingToBePickedUp() const { return m_barrels; }
    
    virtual void setStatus(STATUS st) { m_status = st; }
    virtual STATUS getStatus() const{ return m_status; }
    virtual bool isDead() { return m_status == DEAD? true:false; }
    
    virtual void fireSquirt(Direction dir);
    virtual void dropAGold();
    
private:
    int m_hit;
    int m_squirts;
    int m_sonar;
    int m_goldCounts;
    int m_barrels;
    STATUS m_status;
    void detect();
};

// Class Dirt
class Dirt : public Actor{
public:
    enum STATUS {ALIVE, DEAD};
    Dirt(StudentWorld* sw, int startX, int startY):Actor(sw, IID_DIRT, startX, startY, right, 0.25, 3, false, false, false), m_status(ALIVE){}
    virtual ~Dirt(){}
    virtual void doSomething(){}
    virtual void setStatus(STATUS st) { m_status = st; }
    virtual STATUS getStatus() { return m_status; }
    virtual bool isDead() { return m_status == DEAD? true:false; }
private:
    STATUS m_status;
};

// Class Squirt
class Squirt : public Actor{
public:
    enum STATUS{TEMPORARY, DEAD};
    Squirt(StudentWorld* sw, int x, int y, Direction dir) : Actor(sw, IID_WATER_SPURT, x, y, dir, 1.0, 1, false, false, false), m_status(TEMPORARY), m_dist_count(0) { }
    virtual ~Squirt() {}
    virtual bool isDead() { return m_status == DEAD; }
    virtual void doSomething();
    virtual void setStatus(STATUS st) { m_status = st; }
private:
    STATUS m_status;
    int m_dist_count;
};

// Class Boulder
class Boulder : public Actor{
public:
    enum STATUS{STABLE, DEAD, WAITING, FALLING};
    Boulder(StudentWorld* sw, int x, int y, int starting_count = 0) : Actor(sw, IID_BOULDER, x, y, down, 1., 1, true, false, false), wait_count(starting_count){}
    virtual ~Boulder(){}
    virtual void setStatus(STATUS st) { m_status = st; }
    virtual STATUS getStatus() const { return m_status; }
    virtual void doSomething();
    virtual bool isDead() { return m_status == DEAD? true:false; }
private:
    bool isSupported();
    int wait_count;
    STATUS m_status;
};

// Class ActivatingObject
class ActivatingObject : public Actor{
public:
    enum STATUS{PERMANENT, TEMPORARY, DEAD};
    ActivatingObject(StudentWorld* sw, int imageID, int x, int y, Direction dir = right, double size = 1.0, unsigned int depth = 0, ActivatingObject::STATUS status = PERMANENT, bool pickupable_frackman = true, bool pickupable_protester = false, int lifetime = 9999) : Actor(sw, imageID, x, y, dir, size, depth, false, pickupable_frackman, pickupable_protester), m_status(status), m_life(lifetime), m_life_count(0){}
    virtual ~ActivatingObject(){}
    virtual STATUS getStatus() { return m_status; }
    virtual void setStatus(STATUS st) { m_status = st; }
    virtual bool isDead() { return m_status == DEAD? true:false; }
    virtual void doSomething();
    virtual void playSound();
private:
    virtual void increaseScore() = 0;
    virtual void increaseInventory() = 0;
    STATUS m_status;
    int m_life;
    int m_life_count;
};

// Class Barrels of Oil
class Barrel : public ActivatingObject{
public:
    Barrel(StudentWorld* sw, int x, int y, ActivatingObject::STATUS status) : ActivatingObject(sw, IID_BARREL, x, y, right, 1.0, 2, ActivatingObject::PERMANENT, true, false){}
    virtual ~Barrel(){}
    virtual void playSound();
private:
    virtual void increaseScore();// { getWorld()->increaseScore(1000); }
    virtual void increaseInventory();// { getWorld()->increaseInventory(StudentWorld::BARREL, -1); }
};

// Class Gold Nuggets
class GoldNugget_FrackMan : public ActivatingObject{
public:
    GoldNugget_FrackMan(StudentWorld* sw, int x, int y, ActivatingObject::STATUS status) : ActivatingObject(sw, IID_GOLD, x, y, right, 1.0, 2, status, true, false){}
    virtual ~GoldNugget_FrackMan(){}
private:
    virtual void increaseScore();
    virtual void increaseInventory();
};

class GoldNugget_Protester : public ActivatingObject{
public:
    GoldNugget_Protester(StudentWorld* sw, int x, int y) : ActivatingObject(sw, IID_GOLD, x, y, right, 1.0, 2, ActivatingObject::TEMPORARY, false, true, 100){}
    virtual ~GoldNugget_Protester(){}
private:
    virtual void increaseScore(){}
    virtual void increaseInventory(){}
};
// Class Sonar Kit
class Sonar : public ActivatingObject{
public:
    Sonar(StudentWorld* sw, int lifetime) : ActivatingObject(sw, IID_SONAR, 0, 60, right, 1.0, 2, ActivatingObject::TEMPORARY, true, false, lifetime) { setVisible(true); }
    virtual ~Sonar() {}
private:
    virtual void increaseScore();
    virtual void increaseInventory();
};

// Water Pool
class Water : public ActivatingObject{
public:
    Water(StudentWorld* sw, int x, int y, int lifetime) : ActivatingObject(sw, IID_WATER_POOL, x, y, right, 1.0, 2, ActivatingObject::TEMPORARY, true, false, lifetime) { setVisible(true); }
    virtual ~Water() {}
private:
    virtual void increaseScore();
    virtual void increaseInventory();
};
/*
class GoldNugget_Protester : public GoldNugget{
public:
    GoldNugget_Protester(StudentWorld* sw, int x, int y, ActivatingObject::STATUS status) : GoldNugget(sw, x, y, status){}
    virtual ~GoldNugget_Protester(){}
    virtual void doSomething();
private:
};
 */
/*
class Squirt : public Actor{
public:
    Squirt(StudentWorld* sw, Frackman* fm);
    virtual ~Squirt(){}
    virtual void doSomething();
private:
    Frackman* m_frackman;
};
 */

// Class Coord
class Coord{
public:
    Coord(int rr, int cc): m_r(rr), m_c(cc){}
    int r() const{ return m_r;}
    int c() const{ return m_c;}
private:
    int m_r;
    int m_c;
};
#endif // ACTOR_H_
