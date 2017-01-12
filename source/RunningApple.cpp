/** @package Snake
* @file RunningApple.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/RunningApple.h"
#include <stdlib.h> // for random
#include <ncurses.h>

RunningApple::RunningApple(const Box* box_in, char ch, Type type_in, const Obstacle *obst, int numObst)
{
    velocityX = 0.0;
    velocityY = 0.0;
    accelerationX = 0.0;
    accelerationY = 0.0;
    time = 0.0;
    
    box = box_in;
    obstacle = obst;
    numObstacles = numObst;
    
    pieceChar = ch;
    type = type_in;
    cost = 10;
}

RunningApple::~RunningApple(){}

void RunningApple::move(int intX_in, int intY_in)
{
    intX = intX_in;
    intY = intY_in;
    x = (double)intX;
    y = (double)intY;
}

void RunningApple::newStableApple()
{
    int flag = 1;
    time = 0.0; 
    
    intX = rand() % box->width + box->left;
    intY = rand() % box->height + box->top;
    
    if(obstacle!=NULL){
	for(int k=0;k<numObstacles;k++){
	    for(int i=0;i<obstacle[k].N;i++){
		if(intX == obstacle[k].x[i] && intY == obstacle[k].y[i]){
		    flag = 0;
		    break;
		}
	    }
	}
    }
    
    if(flag==0)
	this->newStableApple();
	
    x = (double)intX;
    y = (double)intY;
    
    velocityX = 0.0;
    velocityY = 0.0;
    
    accelerationX = 0.0;
    accelerationY = 0.0;

}

void RunningApple::newRunningApple(double time0, int maxXspeed, int maxYspeed)
{
<<<<<<< HEAD
=======
    int flag = 1;
>>>>>>> developer
    time = time0;
    
    intX = rand() % box->width + box->left;
    intY = rand() % box->height + box->top;
    
    if(obstacle!=NULL){
	for(int k=0;k<numObstacles;k++){
	    for(int i=0;i<obstacle[k].N;i++){
		if(intX == obstacle[k].x[i] && intY == obstacle[k].y[i]){
		    flag = 0;
		    break;
		}
	    }
	}
    }
    
    if(flag==0)
	this->newRunningApple(time0, maxXspeed, maxYspeed);
    
    x = (double)intX;
    y = (double)intY;
    
    velocityX = ((double)rand() / (double)RAND_MAX-0.5) /maxXspeed;
    velocityY = ((double)rand() / (double)RAND_MAX-0.5) /maxYspeed;
    
    accelerationX = 0.0;
    accelerationY = 0.0;
}

void RunningApple::setAsBonus(Type type)
{
    switch(type){
	case RunningApple::money:
	    pieceChar = '$';
	    colorScheme = 4;
	    cost = 50;
	break;
	
	default:
	break;
    }

}

bool RunningApple::eatingDetection(int xSnake, int ySnake)
{
    if(xSnake == intX && ySnake == intY)
	return true;
	
    return false;
}