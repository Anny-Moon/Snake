/** @package Snake
* @file Snake.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Snake.h"
#include <stdlib.h>
#include <ncurses.h>

Snake::Snake(int length_in, int xStart, int yStart)
{
    int i;
	
    length = length_in;
    headChar = '@';
    bodyChar = 'O';
    
    x = new int [length];
    y = new int [length];
	
    for(i=0;i<length;i++){
	x[i] = xStart - i;
	y[i] = yStart;
    }
}

Snake::~Snake()
{
    delete [] x;
    delete [] y;
}

void Snake::draw() const
{
    int i;
    mvaddch(y[0], x[0], headChar);
	
    for(i=1;i<length;i++){
	mvaddch(y[i], x[i], bodyChar);
    }
}

void Snake::newCoordinates(int arrowKey)
{
    int i;
    
    switch (arrowKey){
	case KEY_LEFT:
	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    x[0] = x[0] - 1;
	break;
	
	case KEY_RIGHT:
	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    x[0] = x[0] + 1;
	break;
	
	case KEY_UP:
	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    y[0] = y[0] - 1;
	break;
	
	case KEY_DOWN:
	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    y[0] = y[0] + 1;
	break;
	
	default:
	break;
    }
}

bool Snake::collisionDetection()
{
    bool answ = false;
    int i;
    
    for(i=4;i<length;i++)
	if(x[0]==x[i] && y[0]==y[i])
	    return true;
	    
    return answ;
}
