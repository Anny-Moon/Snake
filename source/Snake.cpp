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

int Snake::headDirection()
{
    // along y
    if(x[0] == x[1]){
	//to +y
	if(y[0] > y[1])
	    return 2;
	//to -y
	else
	    return -2;
	
    }
    
    // along x
    else if(y[0] == y[1]){
	//to +x @----
	if(x[0] > x[1])
	    return 1;
	//to -x ----@
	else
	    return -1;
    }
    else{
	printf ("Something went wrong\n");
	endwin();
	exit(1);
    }
}

int Snake::tailDirection()
{
    // along y
    if(x[length-1] == x[length - 2]){
	//to +y
	if(y[length-1] > y[length-2])
	    return 2;
	//to -y
	else
	    return -2;
	
    }
    
    // along x
    else if(y[length-1] == y[length - 2]){
	//to +x @----
	if(x[length-1] > x[length-2])
	    return 1;
	//to -x ----@
	else
	    return -1;
    }
    else{
	printf ("Something went wrong\n");
	endwin();
	exit(1);
    }
}
void Snake::changeLength(int newLength)
{
    int i,j;
    int tmpX[length];
    int tmpY[length];
    int tailDir = tailDirection();
    int headDir = headDirection();
    
    for(i=0;i<length;i++){
	tmpX[i] = x[i];
	tmpY[i] = y[i];
    }
    
    delete [] x;
    delete [] y;
    
    x = new int [newLength];
    y = new int [newLength];
    
/*    switch (headDir){
	case 1:
	    x[0] = tmpX[0] + 1;
	    y[0] = tmpY[0];
	    break;
	case -1:
	    x[0] = tmpX[0] - 1;
	    y[0] = tmpY[0];
	    break;
	case 2:
	    x[0] = tmpX[0];
	    y[0] = tmpY[0] + 1;
	    break;
	case -2:
	    x[0] = tmpX[0];
	    y[0] = tmpY[0] - 1;
	    break;
    }
*/    
    for(i=0;i<length;i++){
	x[i] = tmpX[i];
	y[i] = tmpY[i];
    }
    
    for(j=i; j<newLength;j++){
	switch (tailDir){
	    case 1:
		x[j] = x[j-1] + 1;
		y[j] = y[j-1];
		break;
	    case -1:
		x[j] = x[j-1] - 1;
		y[j] = y[j-1];
		break;
	    case 2:
		x[j] = x[j-1];
		y[j] = y[j-1] + 1;
		break;
	    case -2:
		x[j] = x[j-1];
		y[j] = y[j-1] - 1;
		break;
	}
    }
    
    length = newLength;
}
void Snake::draw() const
{
    int i;
    attron(COLOR_PAIR(1));
    mvaddch(y[0], x[0], headChar);
	
    for(i=1;i<length;i++){
	mvaddch(y[i], x[i], bodyChar);
    }
    attroff(COLOR_PAIR(1));
}

void Snake::newCoordinates(int arrowKey)
{
    int i;
    int headDir = headDirection();
    
    switch (arrowKey){
	case KEY_LEFT:
	    if(headDir == 1){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		x[0] = x[0] + 1;
		return;
	    }

	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    x[0] = x[0] - 1;
	break;
	
	case KEY_RIGHT:
	    if(headDir == -1){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		x[0] = x[0] - 1;
		return;
	    }
	    
	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    x[0] = x[0] + 1;
	break;
	
	case KEY_UP:
	    if(headDir == 2){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		y[0] = y[0] + 1;
		return;
	    }
	    
	    for(i=length-1;i>0;i--){
		x[i] = x[i-1];
		y[i] = y[i-1];
	    }
	    y[0] = y[0] - 1;
	break;
	
	case KEY_DOWN:
	    if(headDir == -2){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		y[0] = y[0] - 1;
		return;
	    }
	    
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

bool Snake::collisionDetection(const Box& box)
{
    bool answ = false;
    int i;
    
    /* Self collisions*/
    for(i=4;i<length;i++)
	if(x[0]==x[i] && y[0]==y[i])
	    return true;
    
    /* Collisions with walls*/
    if(y[0] == box.top-1 || y[0] == box.bottom+1)
        return true;
    
    if(x[0] == box.left-1 || x[0] == box.right+1)
        return true;
        
    return answ;
}

void Snake::eatApple(Apple::Type appleType)
{
    switch (appleType){
	case Apple::normal:
	    changeLength(length+1);
	    break;
    }
}