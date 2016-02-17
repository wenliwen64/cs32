#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
void Frackman::doSomething(){
    //Check dead
    if(getCurrentHealth() <= 0)
        return;
    
    //Check overlap
    for(int i = 0; i < SPRITE_WIDTH; i++){
        int x = getX() + i;
        for(int j = 0; j < SPRITE_HEIGHT; j++){
            int y = getY() + j;
            if(x < VIEW_WIDTH && y < VIEW_HEIGHT){
                
                if(getWorld()->getDirt(x, y)->isVisible()){
                    getWorld()->getDirt(x, y)->setVisible(false);
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