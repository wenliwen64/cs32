#include "StudentWorld.h"
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
int StudentWorld::init(){
    m_lastprotestercount = 0;
    m_numprotester = 0;
    const int current_level = getLevel();

    //Initialize Frackman
    m_frackman = new Frackman(this);
    m_frackman->setVisible(true);

    //Initialize dirts
    for(int i = 0; i < VIEW_WIDTH; i++){
        for(int j = 0; j < VIEW_HEIGHT; j++){
            m_dirts[i][j] = new Dirt(this, i, j);
            m_dirts[i][j]->setVisible(true);
            if(i >= (VIEW_WIDTH-SPRITE_WIDTH)/2 && i < (VIEW_WIDTH+SPRITE_WIDTH)/2 && j >= SPRITE_HEIGHT ){
                m_dirts[i][j]->setVisible(false);
                m_dirts[i][j]->setStatus(Dirt::DEAD);
            }
            if(j >= VIEW_HEIGHT - SPRITE_HEIGHT){
                m_dirts[i][j]->setVisible(false);
                m_dirts[i][j]->setStatus(Dirt::DEAD);
            }
        }
    }
    
    // Initialize boulders
    int numBoulders = min(current_level/2 + 2, 6);
    for(int i = 0; i < numBoulders; i++)
        populateBoulders();
    
    //Initialize oil barreles
    int numOilBarrels = min(2 + current_level, 20);
    for(int i = 0; i < numOilBarrels; i++)
        populateBarrels();
    
    // Initialize gold nuggets
    int numGoldNuggets = max(5 - current_level/2, 2);
    for(int i = 0; i < numGoldNuggets; i++)
        populateGoldNuggets();
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
    //cout << "tick" << endl;
    setDisplayText();
    if(theplayerDied()){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    addObjects();
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        if(!(*it)->isDead()){
            actorDoSomething(*it);
            
            if(theplayerDied()){
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            
            if(theplayerCompletedTheCurrentLevel()){
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    playerDoSomething();

    removeDeadActors();
    
    if(theplayerDied()){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    if(theplayerCompletedTheCurrentLevel()){
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    //actorDoSomething();
    //getPlayer()->doSomething();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    
    delete m_frackman;
    
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
    sprintf(stat, "Scr: %06d  Lvl:%2d  Lives: %01d  Hlth: %3d0%%  Water: %2d  Gld: %2d  Sonar: %2d  Oil Left:%2d", score, level, lives, health, squirts, gold, sonar, barrelsLeft);
    string s = string(stat);
    setGameStatText(s);
}

/*
bool StudentWorld::isEnvItem(int x, int y) const{
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++)
        if (((*it)->getID() == IID_BOULDER || (*it)->getID() == IID_DIRT) && ((*it)->getX() == x && (*it)->getY() == y))
            return true;
    return false;
}
*/
void StudentWorld::removeDeadActors(){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); ){
        if((*it)->isDead()){
            (*it)->setVisible(false);
            it = m_vec_actors.erase(it);
        }
        else
            it++;
    }
}

void StudentWorld::populateBoulders(){
    int x_pos = 0;
    int y_pos = 0;
    do{
        x_pos = rand() % (VIEW_WIDTH - SPRITE_WIDTH + 1);
        y_pos = rand() % (VIEW_HEIGHT - 2 * SPRITE_HEIGHT - 20 + 1) + 20;

    }while(occupiedByItemInRadius(x_pos, y_pos, 6.) || occupiedByBoulderRadius(x_pos, y_pos, 6.0) || inTheShaft(x_pos, y_pos));
    
    //cout << x_pos << " " << y_pos << endl;
    Boulder* ptr_bd = new Boulder(this, x_pos, y_pos);
    ptr_bd->setVisible(true);
    m_vec_actors.push_back(ptr_bd);
    
    for(int i = x_pos; i < x_pos+SPRITE_WIDTH; i++)
        for(int j = y_pos; j < y_pos+SPRITE_HEIGHT; j++)
            m_dirts[i][j]->setVisible(false);
}

void StudentWorld::populateBarrels(){
    int x_pos = 0;
    int y_pos = 0;
    do{
        x_pos = rand() % (VIEW_WIDTH - SPRITE_HEIGHT + 1);
        y_pos = rand() % (VIEW_HEIGHT - 2 * SPRITE_HEIGHT + 1);
    }while(occupiedByItemInRadius(x_pos, y_pos, 6) || occupiedByBoulderRadius(x_pos, y_pos, 6.0) || inTheShaft(x_pos, y_pos));
    
    //cout << "barrels " << x_pos << " " << y_pos << endl;
    Barrel* ptr_barrel = new Barrel(this, x_pos, y_pos, ActivatingObject::PERMANENT);
    ptr_barrel->setVisible(false);
    m_vec_actors.push_back(ptr_barrel);
    m_frackman->increaseNumberOfBarrelsRemainingToBePickedUp(1);
}

void StudentWorld::populateGoldNuggets(){//TODO: duplicated code
    int x_pos = 0;
    int y_pos = 0;
    do{
        x_pos = rand() % (VIEW_WIDTH - SPRITE_HEIGHT + 1);
        y_pos = rand() % (VIEW_HEIGHT - 2 * SPRITE_HEIGHT + 1);
    }while(occupiedByItemInRadius(x_pos, y_pos, 6.0) || occupiedByBoulderRadius(x_pos, y_pos, 6.0) || inTheShaft(x_pos, y_pos));
    
    //cout << "gold " << x_pos << " " << y_pos << endl;
    GoldNugget_FrackMan* ptr_gold = new GoldNugget_FrackMan(this, x_pos, y_pos, ActivatingObject::PERMANENT);
    ptr_gold->setVisible(false);
    m_vec_actors.push_back(ptr_gold);
}

void StudentWorld::populateSonar(){
    int G = getCurrentGameLevel()*25 + 300;
    int random = rand() % G;
    if(random == 0){
        Sonar* ptr_sonar = new Sonar(this, max(100, 300 - 10 * getCurrentGameLevel()));
        ptr_sonar->setVisible(true);
        m_vec_actors.push_back(ptr_sonar);
    }
}

void StudentWorld::populateRegularProtester(){
    int ticksToWaitBetweenMoves = max(0, 3 - getCurrentGameLevel());
    Protester* pt = new Protester(this, IID_PROTESTER, ticksToWaitBetweenMoves);
    pt->setVisible(true);
    m_lastprotestercount = 0;
    m_vec_actors.push_back(pt);
    //cout << "happy" << endl;
}

void StudentWorld::addObjects(){
    int G = getCurrentGameLevel()*25 + 300;
    int random = rand() % G;
    if(random == 0){
        int random1 = rand() % 5;
        if(random1 == 0){
            Sonar* ptr_sonar = new Sonar(this, max(100, 300 - 10 * getCurrentGameLevel()));
            ptr_sonar->setVisible(true);
            m_vec_actors.push_back(ptr_sonar);
        }
        else{
            int x_pos = 0;
            int y_pos = 0;
            int sz = 4;
            do{
                x_pos = rand() % (VIEW_WIDTH - SPRITE_HEIGHT + 1);
                y_pos = rand() % (VIEW_HEIGHT - SPRITE_HEIGHT + 1);
            }while(occupiedByDirt(x_pos, y_pos, sz) || occupiedByItem(x_pos, y_pos, sz));
            Water* ptr_water = new Water(this, x_pos, y_pos, max(100, 300 - 10 * getCurrentGameLevel()));

            ptr_water->setVisible(true);
            m_vec_actors.push_back(ptr_water);
        }
    }
    
    // Add Protester
    int T = max(25, 200 - getCurrentGameLevel());
    int tt = 2 + 1.5 * getCurrentGameLevel();
    int P = min(15, tt);
    if(m_lastprotestercount % T == 0 && m_numprotester < P)
        populateRegularProtester();
    m_lastprotestercount++;
}

bool StudentWorld::occupiedByBoulder(int x, int y, int size){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if((*it)->isBlockable() && (*it)->getX() == x + i && (*it)->getY() == y + j)
                    return true;
            }
        }
    }
    return false;
}


bool StudentWorld::occupiedByDirt(int x, int y, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(isDirtVisible(x + i, y + j))
               return true;
        }
    }
    
    return false;
}

bool StudentWorld::occupiedByItem(int x, int y, int size){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if((*it)->getX() == x + i && (*it)->getY() == y + j)
                    return true;
            }
        }
    }
    
    return false;
}

bool StudentWorld::occupiedByItemInRadius(int x, int y, double R){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++)
        if((*it)->inRadius(x, y, R))
            return true;
    return false;
}

bool StudentWorld::occupiedByBoulderRadius(int x, int y, double R){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        if((*it)->isBlockable() && (*it)->inRadius(x, y, R))
            return true;
    }
    return false;
}

bool StudentWorld::isplayerAround(int x, int y, double R){
    return m_frackman->inRadius(x, y, R)? true:false;
}

bool StudentWorld::occupiedByAgent(int x, int y, int size){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        if((*it)->canPickThingsUp()){
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    if((*it)->getX() == x + i && (*it)->getY() == y + j)
                        return true;
                }
            }
        }
    }
    return false;
}

void StudentWorld::increaseInventory(ITEM_NAME item_name, int howMuch){
    switch(item_name){
        case GOLD:
            m_frackman->increaseGoldCount(howMuch);
            break;
        case WATER:
            m_frackman->increaseSquirtsLeftInSquirtGun(howMuch);
            break;
        case BARREL:
            m_frackman->increaseNumberOfBarrelsRemainingToBePickedUp(howMuch);
            break;
        case SONAR:
            m_frackman->increaseSonarChargeCount(howMuch);
            break;
        default:
            break;
    }
}

void StudentWorld::setVisibleInRadius(int x, int y, double R){
    for(auto it = m_vec_actors.begin(); it != m_vec_actors.end(); it++){
        if((*it)->isPickUpAbleByFrackman() && (*it)->inRadius(x, y, R))
            (*it)->setVisible(true);
    }
}

void StudentWorld::getFrackmanAnnoyed(int damage){
    m_frackman->decreaseHealth(damage);
}

bool StudentWorld::clearDirtInStraightLine(int sx, int sy, int ex, int ey, int size){
    if(sx != ex && sy != ey)
        return false;
    else if(sx == ex){
        int start_point = sy >= ey? ey:sy;
        
        for(int i = 0; i < abs(sy - ey); i++)
            for(int j = 0; j < size; j++)
                if(isDirtVisible(sx + j, start_point + i))
                    return false;
    }
    else if(sy == ey){
        int start_point = sx >= ex? ex:sx;
        for(int i = 0; i < abs(sx - ex); i++)
            for(int j = 0; j < size; j++)
                if(isDirtVisible(start_point + i, sy + j)){

                    return false;
                }
    }
    
    return true;
}