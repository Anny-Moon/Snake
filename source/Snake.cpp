/* Copyright 2017 Anna Sinelnikova
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
*/

/** @package Snake
* @file Snake.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Snake.h"
#include <stdlib.h>
#include <ncurses.h>

Snake::Snake(int length_in, int xStart, int yStart, int dTime_in)
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
    
    dTime = dTime_in;
    
    keyboardMode = 1;
    colorScheme = 1;
}

Snake::~Snake()
{
    delete [] x;
    delete [] y;
}

int Snake::findOptimalInitPosition(const Obstacle* obstacle, int numObstacles, const Box& box)
{
    int answ = 0;
    int flag = 1;
//    int x0 = x[0];
//    int y0 = y[0];
    
    while(1){
	flag=1;
	
	for(int i=0;i<length;i++){
	    if(!Obstacle::isPixelFree(x[i], y[i], obstacle, numObstacles)){
		flag = 0;
		break;
	    }
	
	}
	
	// if there is no free pixel between snake's head and obstacles
	// 0000@
	if(!Obstacle::isPixelFree(x[0]+1, y[0], obstacle, numObstacles))
	    flag = 0;
	
	if(flag==0){
	    if(y[0]+1<box.bottom){ //shift down
		for(int j=0;j<length;j++)
		    y[j]+=1;
		answ=1;
	    }
	    else if(x[0]+1<box.right){ //shift right
		for(int j=0;j<length;j++)
		    x[j]+=1;
		answ=1;
	    }
	    else 
		return -1;
	}
	else //flag = 1 - did nothing
	    return answ;
    }
    return answ;
}

int Snake::headDirection()
{
    // along y
    if(x[0] == x[1]){
	//to +y
	if(y[0] == y[1]+1 || y[0]+1<y[1]) // after || - for periodic boundry conditions
	    return 2;
	//to -y
	else
	    return -2;
	
    }
    
    // along x
    else if(y[0] == y[1]){
	//to +x ----@
	if(x[0] == x[1]+1 || x[0]+1<x[1]) // for periodic boundry conditions
	    return 1;
	//to -x @----
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
//    int headDir = headDirection();
    
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

void Snake::erase() const
{
    int i;
	
    for(i=0;i<length;i++){
	mvaddch(y[i], x[i], ' ');
    }
}

void Snake::draw() const
{
    int i;
    attron(COLOR_PAIR(colorScheme));
    mvaddch(y[0], x[0], headChar);
	
    for(i=1;i<length;i++){
	mvaddch(y[i], x[i], bodyChar);
    }
    attroff(COLOR_PAIR(colorScheme));
}

void Snake::newCoordinates(int arrowKey)
{
    int i;
    int headDir = headDirection();
    
    if(keyboardMode == 1){
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
	    if(headDir == 1){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		x[0] = x[0] + 1;
		return;
	    }
	    
	    if(headDir == -1){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		x[0] = x[0] - 1;
		return;
	    }
	    
	    if(headDir == 2){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		y[0] = y[0] + 1;
		return;
	    }
	    
	    if(headDir == -2){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		y[0] = y[0] - 1;
		return;
	    }
	break;
    }// end of case
    }//end of if
    
    if(keyboardMode == 2){
    switch (arrowKey){
    	case 'A'://left
    	case 'a':
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
	
	case 'D'://right
	case 'd':
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
	
	case 'W'://up
	case 'w':
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
	
	case 'S'://down
	case 's':
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
	    if(headDir == 1){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		x[0] = x[0] + 1;
		return;
	    }
	    
	    if(headDir == -1){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		x[0] = x[0] - 1;
		return;
	    }
	    
	    if(headDir == 2){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		y[0] = y[0] + 1;
		return;
	    }
	    
	    if(headDir == -2){
		for(i=length-1;i>0;i--){
		    x[i] = x[i-1];
		    y[i] = y[i-1];
		}
		y[0] = y[0] - 1;
		return;
	    }
	break;
    }// end of case
    }//end of if
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

bool Snake::collisionDetection(const Obstacle* obstacle, int numObstacles)
{
/*    bool answ = false;
    int i, k;
    
    for(k=0;k<N;k++){
	for(i=0;i<obstacle[k].N;i++){
	    if(x[0]==obstacle[k].x[i] && y[0]==obstacle[k].y[i])
		return true;
	}
    }
    return answ;
*/
    if(!Obstacle::isPixelFree(x[0], y[0], obstacle, numObstacles))
	return true;
    return false;
}

void Snake::eatApple(Apple::Type appleType)
{
    switch (appleType){
	case Apple::normal:
	    changeLength(length+1);
	    break;
	default:
	    break;
    }
}