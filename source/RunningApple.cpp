/** @package Snake
* @file RunningApple.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/RunningApple.h"
#include <stdlib.h> // for random
#include <ncurses.h>

RunningApple::RunningApple(const Box* box_in, char ch, Type type_in)
{
    velocityX = 0.0;
    velocityY = 0.0;
    accelerationX = 0.0;
    accelerationY = 0.0;
    time = 0.0;
    
    box = box_in;
    pieceChar = ch;
    type = type_in;
}

RunningApple::~RunningApple(){}

void RunningApple::newStableApple()
{
    time =0.0; 
    
    intX = rand() % box->width + box->left;
    intY = rand() % box->height + box->top;
    x = (double)intX;
    y = (double)intY;
    
    velocityX = 0.0;
    velocityY = 0.0;
    
    accelerationX = 0.0;
    accelerationY = 0.0;

}

void RunningApple::newRunningApple()
{
    time = 0.0;
    
    intX = rand() % box->width + box->left;
    intY = rand() % box->height + box->top;
    x = (double)intX;
    y = (double)intY;
    
    velocityX = ((double)rand() / (double)RAND_MAX-0.5) /80;
    velocityY = ((double)rand() / (double)RAND_MAX-0.5) /80;
    
    accelerationX = 0.0;
    accelerationY = 0.0;
}

bool RunningApple::eatingDetection(int xSnake, int ySnake)
{
    if(xSnake == intX && ySnake == intY)
	return true;
	
    return false;
}