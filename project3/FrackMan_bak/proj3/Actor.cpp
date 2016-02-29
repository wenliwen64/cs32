#include "Actor.h"
#include "StudentWorld.h"
#include <queue>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Frackman::fireSquirt(Direction dir){
    int start_x = getX();
    int start_y = getY();
    switch(dir){
        case right:
            start_x += 4;
            break;
        case left:
            start_x -= 4;
            break;
        case up:
            start_y += 4;
            break;
        case down:
            start_y -= 4;
            break;
        default:
            break;
    }
    
    if(start_x < 0 || start_x > (VIEW_WIDTH - 4) || start_y < 0 || start_y > (VIEW_HEIGHT - 4)){
        getWorld()->playSound(SOUND_PLAYER_SQUIRT);
        increaseSquirtsLeftInSquirtGun(-1);
        return;
    }
    else if(getWorld()->occupiedByBoulderRadius(start_x, start_y, 3.0) || getWorld()->occupiedByDirt(start_x, start_y, 4)){
        increaseSquirtsLeftInSquirtGun(-1);
        return;
    }
        
    Squirt* ptr_squirt = new Squirt(getWorld(), start_x, start_y, getDirection());
    //cout << getX() << " " << getY() << endl;
    //cout << "non-blocked" << endl;
    ptr_squirt->setVisible(true);
    //cout << ptr_squirt->getX() << "=====" << ptr_squirt->getY() << " " << ptr_squirt->isVisible() << " " << ptr_squirt->getID() << endl;

    getWorld()->addActor(ptr_squirt);
    increaseSquirtsLeftInSquirtGun(-1);
}

void Frackman::detect(){
    if(getSonarChargeCount() > 0){
        getWorld()->setVisibleInRadius(getX(), getY(), 12.0);
        increaseSonarChargeCount(-1);
        return;
    }
    else
        return;
}

void Frackman::dropAGold(){
    if(getGoldCount() > 0){
        GoldNugget_Protester* ptr_gold = new GoldNugget_Protester(getWorld(), getX(), getY());
        ptr_gold->setVisible(true);
        getWorld()->addActor(ptr_gold);
        increaseGoldCount(-1);
        
    }
}

void Frackman::doSomething(){
    //Check dead
    if(getCurrentHealth() <= 0){
        setStatus(DEAD);
        return;
    }
    
    int current_x = getX();
    int current_y = getY();
    
    // Check overlap with boulder
    //if(getWorld()->occupiedByBoulder(current_x, current_y, 4))
        
    
    // Check overlap
    bool sound_flag = false;
    
    for(int i = 0; i < SPRITE_WIDTH; i++){
        int x = current_x + i;
        for(int j = 0; j < SPRITE_HEIGHT; j++){
            int y = current_y + j;
            if(x < VIEW_WIDTH && y < VIEW_HEIGHT){
                if(getWorld()->isDirtVisible(x, y)){
                    getWorld()->setDirtInVisible(x, y);
                    sound_flag = true;
                }
            }
        }
    }
    
    if(sound_flag) getWorld()->playSound(SOUND_DIG);
    
    int ch;
    if(getWorld()->getKey(ch) == true){
        int next_x = 0;
        int next_y = 0;
        //cout << getX() << " " << getY() << endl;
        switch(ch){
            case KEY_PRESS_LEFT:
                if(getDirection() != left ){
                    setDirection(left);
                    break;
                }
                else{
                    //cout << "MOVE!" << endl;
                    next_x = current_x - 1;
                    next_y = current_y;
                    (next_x >= 0 && !getWorld()->occupiedByBoulderRadius(next_x, next_y, 3))? moveTo(next_x, next_y):moveTo(current_x, current_y);
                    break;
                }
            case KEY_PRESS_RIGHT:
                if(getDirection() != right){
                    setDirection(right);
                    break;
                }
                else{
                    next_x = current_x + 1;
                    next_y = current_y;
                    (next_x <= (VIEW_WIDTH - SPRITE_WIDTH) && !getWorld()->occupiedByBoulderRadius(next_x, next_y, 3))? moveTo(next_x, next_y):moveTo(current_x, current_y);
                    break;
                }
            case KEY_PRESS_UP:
                if(getDirection() != up){
                    setDirection(up);
                    break;
                }
                else{
                    next_x = current_x;
                    next_y = current_y + 1;
                    (next_y <= (VIEW_HEIGHT - SPRITE_HEIGHT) && !getWorld()->occupiedByBoulderRadius(next_x, next_y, 3.))? moveTo(next_x, next_y):moveTo(current_x, current_y);
                    break;
                }
            case KEY_PRESS_DOWN:
                if(getDirection() != down){
                    setDirection(down);
                    break;
                }
                else{
                    next_x = current_x;
                    next_y = current_y - 1;
                    (next_y >= 0 && !getWorld()->occupiedByBoulderRadius(next_x, next_y, 3))? moveTo(next_x, next_y):moveTo(current_x, current_y);
                    break;
                }
            case KEY_PRESS_SPACE:
                fireSquirt(getDirection());
                break;
            case KEY_PRESS_ESCAPE:
                setHealth(0);
                break;
            case 'z':
                detect();
                break;
            case 'Z':
                detect();
                break;
            case KEY_PRESS_TAB:
                dropAGold();
                break;
            default:
                break;
        }
    }
}

// Class Squirt
void Squirt::doSomething(){
    //cout << m_dist_count << " " << endl;
    if(isDead())
        return;
    int next_x = getX();
    int next_y = getY();
    switch(getDirection()){
        case right:
            next_x++;
            break;
        case left:
            next_x--;
            break;
        case up:
            next_y++;
            break;
        case down:
            next_y--;
            break;
        default:
            break;
    }
    
    if(next_x < 0 || next_x >= VIEW_WIDTH || next_y < 0 || next_y >= VIEW_HEIGHT){
        setStatus(DEAD);
        return;
    }
    else if(getWorld()->occupiedByBoulderRadius(next_x, next_y, 3.0) || getWorld()->occupiedByDirt(next_x, next_y, 4)){
        setStatus(DEAD);
        return;
    }
    else{
        moveTo(next_x, next_y);
        m_dist_count++;
    }
    
    if(m_dist_count >= 4)
        setStatus(DEAD);
}

// Class Boulder
void Boulder::doSomething(){
    int current_x = getX();
    int current_y = getY();
    //if (getStatus() == DEAD)
    //  return;
    //printf("isSupported()? %s\n", isSupported()? "true":"false");
    switch(getStatus()){
        case STABLE:
            if(isSupported())
                return;
            else{
                setStatus(WAITING);
                //printf("status = %d\n", Actor::WAITING);
                return;
            }
            break;
        case DEAD:
            return;
            break;
        case WAITING:
            if(wait_count < 30){
                //printf("wait_count = %d\n", wait_count);
                wait_count++;
            }
            else
                setStatus(FALLING);
            break;
        case FALLING:
            if(current_y == 0 || isSupported())
                setStatus(DEAD);
            else{
                //if(getWorld()->isplayerAround(getX(), getY(), 3.0))
                moveTo(current_x, current_y - 1);
            }
            break;
        default:
            break;
    }
}

bool Boulder::isSupported(){
    int current_x = getX();
    int current_y = getY();
    return (getWorld()->isDirtVisible(current_x, current_y - 1) || getWorld()->isDirtVisible(current_x + 1, current_y - 1) || getWorld()->isDirtVisible(current_x + 2, current_y - 1) || getWorld()->isDirtVisible(current_x + 3, current_y - 1))? true:false;
    
}

// class ActivatingObject
void ActivatingObject::playSound(){
    getWorld()->playSound(SOUND_GOT_GOODIE);
}

void ActivatingObject::doSomething(){
    //cout << getID() << "->ID " << getWorld()->isplayerAround(getX(), getY(), 3.0) << endl;
    if(isDead()){
        return;
    }
    if(m_life_count >= m_life){
        setStatus(DEAD);
        return;
    }
    if(getWorld()->isplayerAround(getX(), getY(), 4.0)){
        setVisible(true);
    }
    if(
        (isPickUpAbleByFrackman() && getWorld()->isplayerAround(getX(), getY(), 3.0))
    // || (isPickUpAbleByProtester() && getWorld()->isprotesterAround(getX(), getY(), 3.0))
    ){
        //cout << "Around!!!" << endl;
        setStatus(DEAD);
        playSound();
        increaseScore();
        increaseInventory();
    }
    if(getStatus() == TEMPORARY)
        m_life_count++;
}

// class Barrel
void Barrel::playSound(){
    getWorld()->playSound(SOUND_FOUND_OIL);
}

void Barrel::increaseScore(){
    getWorld()->increaseScore(1000);
}

void Barrel::increaseInventory(){
    getWorld()->increaseInventory(StudentWorld::BARREL, -1);
}

// class GoldNuggets
void GoldNugget_FrackMan::increaseScore(){
    getWorld()->increaseScore(10);
}

void GoldNugget_FrackMan::increaseInventory(){
    getWorld()->increaseInventory(StudentWorld::GOLD, 1);
}

// class Sonar Kit
void Sonar::increaseScore(){
    getWorld()->increaseScore(75);
}

void Sonar::increaseInventory(){
    getWorld()->increaseInventory(StudentWorld::SONAR, 1);
}

// class Water Pool
void Water::increaseScore(){
    getWorld()->increaseScore(100);
}

void Water::increaseInventory(){
    getWorld()->increaseInventory(StudentWorld::WATER, 5);
}
/*
void GoldNugget_FrackMan::doSomething(){
    if(this->isDead())
        return;
    else if(!isVisible() && getWorld()->isplayerAround(getX(), getY(), 4.0)){
        setVisible(true);
        return;
    }
    else if(getStatus() == PERMANENT && getWorld()->isplayerAround(getX(), getY(), 3.0)){
        setStatus(DEAD);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(10);
        getWorld()->increaseInventory(StudentWorld::GOLD, 1);
    }
    else{
        return;
    }
}
*/

// Class Protester
void Protester::doSomething(){
    if(isDead())
        return;
    else if(inRest()){
        m_rest_ticks++;
        return;
    }
    else if(isLeaving()){
        setDead();
        m_rest_ticks++;
        //TODO:
        //if(atExit()){
            //setDead();
            //return;
        //}
        //else
            //return;
        
    }
    else if(seeAndFaceToPlayer()){
        if(!shoutInLastNonRestingTicks()){
            //cout << "shout count " << m_shout_count << endl;
            getWorld()->playSound(SOUND_PROTESTER_YELL);
            getWorld()->getFrackmanAnnoyed(2);
            m_last_shout_ticks_lapsed = 0;
            m_rest_ticks++;
            return;
        }
        else{
            return;
        }
    }
    else if(alignWithFrackman() && awayFromFrackman() && getWorld()->clearDirtInStraightLine(getX(), getY(), getWorld()->getPlayerX(), getWorld()->getPlayerY(), 4)){
        setDirection(towardFrackmanDirection());
        switch(towardFrackmanDirection()){
            case left:
                moveTo(getX() - 1, getY());
                break;
            case right:
                moveTo(getX() + 1, getY());
                break;
            case up:
                moveTo(getX(), getY() + 1);
                break;
            case down:
                moveTo(getX(), getY() - 1);
                break;
            default:
                break;
        }
        setNumSquaresToMoveInCurrentDirection(0);
        m_last_shout_ticks_lapsed++;
        m_rest_ticks++;
        return;
    }
    else if(!alignWithFrackman() || !getWorld()->clearDirtInStraightLine(getX(), getY(), getWorld()->getPlayerX(), getWorld()->getPlayerY(), 4)){
        //cout << alignWithFrackman() << " " << awayFromFrackman() << " " << getWorld()->clearDirtInStraightLine(getX(), getY(), getWorld()->getPlayerX(), getWorld()->getPlayerY(), 4) << endl;
        //cout << "cannot see frackman!" << endl;
        int next_x = getX();
        int next_y = getY();
        Direction dir = none;
        m_num_squares_to_move_in_current_direction--;
        if(m_num_squares_to_move_in_current_direction <= 0){
            do{
                dir = (Direction)(rand() % 4 + 1);
                next_x = getX();
                next_y = getY();
                switch(dir){
                    case left:
                        next_x = getX() - 1;
                        next_x = next_x < 0? -1:next_x;
                        break;
                    case right:
                        next_x = getX() + 1;
                        next_x = next_x > 60? -1:next_x;
                        break;
                    case up:
                        next_y = getY() + 1;
                        next_y = next_y > 60? -1:next_y;
                        break;
                    case down:
                        next_y = getY() - 1;
                        next_y = next_y < 0? -1:next_y;
                        break;
                    default:
                        break;
                }
                
            }while(next_x == -1 || next_y == -1 || getWorld()->occupiedByBoulderRadius(next_x, next_y, 3.0) || getWorld()->occupiedByDirt(next_x, next_y, 4));
            
            //cout << dir << " direction!" << endl;
            setDirection(dir);
            setNumSquaresToMoveInCurrentDirection(8 + rand()%53);
            //cout << m_num_squares_to_move_in_current_direction << " numsquares === m_perp_turn " << m_perp_turn_ticks_count << endl;
            
        }
        else if(atIntersection() && m_perp_turn_ticks_count > 200){
            Direction dir = getTurnDirection();
            setDirection(dir);
            setNumSquaresToMoveInCurrentDirection(generateNumSquaresToMoveInCurrentDirection());
            m_perp_turn_ticks_count = 0;
        }

    }
    
    int next_x = getX();
    int next_y = getY();
    switch(getDirection()){
        case left:
            next_x = getX() - 1;
            next_x = next_x < 0? -1:next_x;
            break;
        case right:
            next_x = getX() + 1;
            next_x = next_x > 60? -1:next_x;
            break;
        case up:
            next_y = getY() + 1;
            next_y = next_y > 60? -1:next_y;
            break;
        case down:
            next_y = getY() - 1;
            next_y = next_y < 0? -1:next_y;
            break;
        default:
            break;
    }
    if(next_x == -1 || next_y == -1 || getWorld()->occupiedByBoulderRadius(next_x, next_y, 3.0) || getWorld()->occupiedByDirt(next_x, next_y, 4)){
        setNumSquaresToMoveInCurrentDirection(0);
        return;
    }
    else
        moveTo(next_x, next_y);
    
    m_rest_ticks++;
    m_perp_turn_ticks_count++;
    m_last_shout_ticks_lapsed++;
    //cout << "m_perp_turn " << m_perp_turn_ticks_count << endl;
    return;
}

bool Protester::alignWithFrackman() {
    return getX() == getWorld()->getPlayerX() || getY() == getWorld()->getPlayerY();
}

bool Protester::awayFromFrackman(){
    if(abs(getX() - getWorld()->getPlayerX()) > 4|| abs(getY() - getWorld()->getPlayerY()) > 4){
        return true;
    }
    else
        return false;
}

bool Protester::shoutInLastNonRestingTicks(){
    if(m_last_shout_ticks_lapsed >= 15)
        return false;
    else
        return true;
}

bool Protester::seeAndFaceToPlayer(){
    if(getX() >= getWorld()->getPlayerX() - 4 && getX() <= getWorld()->getPlayerX() + 4 && getY() >= getWorld()->getPlayerY() -4
       && getY() <= getWorld()->getPlayerY() + 4){
        switch(getDirection()){
            case left:
                if(getX() >= getWorld()->getPlayerX())
                    return true;
                else
                    return false;
                break;
            case right:
                if(getX() <= getWorld()->getPlayerX())
                    return true;
                else
                    return false;
                break;
            case up:
                if(getY() <= getWorld()->getPlayerY())
                    return true;
                else
                    return false;
                break;
            case down:
                if(getY() >= getWorld()->getPlayerY())
                    return true;
                else
                    return false;
                break;
            default:
                return false;
                break;
            
        }
    }
    else
        return false;
}

GraphObject::Direction Protester::towardFrackmanDirection(){
    int playerX = getWorld()->getPlayerX();
    int playerY = getWorld()->getPlayerY();
    
    int X = getX();
    int Y = getY();
    
    if(X >= playerX && Y == playerY)
        return left;
    if(X <= playerX && Y == playerY)
        return right;
    if(X == playerX && Y >= playerY)
        return down;
    if(X == playerX && Y <= playerY)
        return up;
    else
        exit(-1);
}

bool Protester::atIntersection(){
    
    int x = getX();
    int y = getY();
    if(getDirection() == left || getDirection() == right){
        for(int i = 0; i < 2; i++){
            switch(i){
                case 0://down
                    y = getY() - 1;
                    y = y < 0? -1:y;
                    break;
                case 1://up
                    y = getY() + 1;
                    y = y > 60? -1:y;
                    break;
                default:
                    break;
            }
        
            if( x != -1 && y != -1 && !getWorld()->occupiedByDirt(x, y, 4) && !getWorld()->occupiedByBoulderRadius(x, y, 3.0) )
                return true;
        }
    }
    else{
        for(int i = 0; i < 2; i++){
            switch(i){
                case 0://left
                    x = getX() - 1;
                    x = x < 0? -1:x;
                    break;
                case 1://right
                    x = getX() + 1;
                    x = x > 60? -1:x;
                    break;
                default:
                    break;
            }
            
            if( x != -1 && y != -1 &&!getWorld()->occupiedByDirt(x, y, 4) && !getWorld()->occupiedByBoulderRadius(x, y, 3.0) )
                return true;
        }
    }
    return false;
}

GraphObject::Direction Protester::getTurnDirection(){
    int x = getX();
    int y = getY();
    vector<GraphObject::Direction> vec_dir;
    if(getDirection() == left || getDirection() == right){
        for(int i = 0; i < 2; i++){
            switch(i){
                case 0://down
                    y = getY() - 1;
                    y = y < 0? -1:y;
                    break;
                case 1://up
                    y = getY() + 1;
                    y = y > 60? -1:y;
                    break;
                default:
                    break;
            }
            
            if( x != -1 && y != -1 && !getWorld()->occupiedByDirt(x, y, 4) && !getWorld()->occupiedByBoulderRadius(x, y, 3.0) )
                i == 0? vec_dir.push_back(down):vec_dir.push_back(up);
        }
    }
    else{
        for(int i = 0; i < 2; i++){
            switch(i){
                case 0://left
                    x = getX() - 1;
                    x = x < 0? -1:x;
                    break;
                case 1:
                    x = getX() + 1;
                    x = x > 60? -1:x;
                    break;
                default:
                    break;
            }
            
            if( x != -1 && y != -1 && !getWorld()->occupiedByDirt(x, y, 4) && !getWorld()->occupiedByBoulderRadius(x, y, 3.0) )
                i == 0? vec_dir.push_back(left):vec_dir.push_back(right);
        }
    }

    return vec_dir.size() == 2? vec_dir[rand()%2]:vec_dir[0];
}

bool pathExists(StudentWorld* sw, char maze[64][64], int nRows, int nCols, int sr, int sc, int er, int ec){
    queue<Coord> coordQueue;
    
    Coord start_point(sr, sc);
    Coord end_point(er, ec);
    coordQueue.push(start_point);
    maze[start_point.r()][start_point.c()] = 'O';
    
    while(!coordQueue.empty()){
        Coord curr = coordQueue.front();
        //cerr << "( " << curr.r() << ", " << curr.c() << " )" << endl;
        coordQueue.pop();
        
        int curr_r = curr.r();
        int curr_c = curr.c();
        if(curr_r == end_point.r() && curr_c == end_point.c())
            return true;
        else{
            if(curr_c + 1 < nCols && !sw->occupiedByDirt(curr_r, curr_c, 4) && maze[curr_r][curr_c + 1] == '.'){ // East
                Coord next_point(curr_r,  curr_c + 1);
                maze[curr_r] [curr_c + 1] = 'O';
                coordQueue.push(next_point);
            }
            if(curr_r - 1 >= 0 && !sw->occupiedByDirt(curr_r, curr_c, 4) && maze[curr_r - 1][curr_c] == '.'){ // North
                Coord next_point(curr_r - 1,  curr_c);
                maze[curr_r - 1] [curr_c] = 'O';
                coordQueue.push(next_point);
            }
            if(curr_c - 1 >= 0 && maze[curr_r ][curr_c - 1] == '.'){ // West
                Coord next_point(curr_r,  curr_c - 1);
                maze[curr_r][curr_c - 1] = 'O';
                coordQueue.push(next_point);
            }
            if(curr_r + 1 < nRows && maze[curr_r + 1][curr_c] == '.'){ // South
                Coord next_point(curr_r + 1,  curr_c);
                maze[curr_r + 1][curr_c] = 'O';
                coordQueue.push(next_point);
            }
        }
    }
    return false;
}