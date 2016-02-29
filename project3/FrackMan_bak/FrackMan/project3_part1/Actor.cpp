#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
void Frackman::doSomething(){
    //Check dead
    if(getCurrentHealth() <= 0){
        setStatus(Actor::DEAD);
        return;
    }
    
    //Check overlap
    for(int i = 0; i < SPRITE_WIDTH; i++){
        int x = getX() + i;
        for(int j = 0; j < SPRITE_HEIGHT; j++){
            int y = getY() + j;
            if(x < VIEW_WIDTH && y < VIEW_HEIGHT){
                
                if(getWorld()->isDirtVisible(x, y)){
                    getWorld()->setDirtVisible(x, y, false);
                    getWorld()->playSound(SOUND_DIG);
                }
            }
        }
    }
    
    int ch;
    if(getWorld()->getKey(ch) == true){
        switch(ch){
            case KEY_PRESS_LEFT:
                setDirection(left);
                getX()-1 >= 0? moveTo(getX() - 1, getY()):moveTo(getX(), getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                getX()+1 <= (VIEW_WIDTH - SPRITE_WIDTH)? moveTo(getX() + 1, getY()):moveTo(getX(), getY());
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                getY()+1 <= (VIEW_HEIGHT - SPRITE_HEIGHT)? moveTo(getX(), getY() + 1):moveTo(getX(), getY());
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                getY()-1 >= 0? moveTo(getX(), getY() - 1):moveTo(getX(), getY());
                break;
            case KEY_PRESS_ESCAPE:
                setHealth(0);
                break;
            default:
                break;
        }
    }
}

// class Boulder
Boulder::Boulder(StudentWorld* sw, int x, int y) :Actor(sw, IID_BOULDER, x, y, down, 1., 1){
}

void Boulder::doSomething(){
    static int wait_count = 0;
    int current_x = getX();
    int current_y = getY();
    //if (getStatus() == DEAD)
    //  return;
    //printf("isSupported()? %s\n", isSupported()? "true":"false");
    switch(getStatus()){
        case Actor::STABLE:
            if(isSupported())
                return;
            else{
                setStatus(Actor::WAITING);
                //printf("status = %d\n", Actor::WAITING);
                return;
            }
            break;
        case Actor::DEAD:
            return;
            break;
        case Actor::WAITING:
            if(wait_count < 30){
                //printf("wait_count = %d\n", wait_count);
                wait_count++;
            }
            else
                setStatus(FALLING);
            break;
        case Actor::FALLING:
            if(current_y == 0 || isSupported())
                setStatus(DEAD);
            else
                moveTo(current_x, current_y - 1);
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