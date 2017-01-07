/** @package Snake
* @file Obstacle.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Obstacle.h"
#include <ncurses.h>

Obstacle::Obstacle(){}

void Obstacle::init(int width_in, int height_in, int xStart_in, int yStart_in)
{
    int i, j;
    width = width_in;
    height = height_in;
    xStart = xStart_in;
    yStart = yStart_in;
    
    top = yStart;
    bottom = yStart + height - 1;
    left = xStart;
    right = xStart + width - 1;
    
    N = width*height;
    x = new int[N];
    y = new int[N];
    
    for(i=0;i<height;i++){
	for(j=0;j<width;j++){
	    x[i*width+j] = left + j;
	    y[i*width+j] = top + i;
	}
    }
}

Obstacle::~Obstacle()
{
    if(x != NULL)
	delete [] x;
    
    if(y != NULL)
    delete [] y;
}

void Obstacle::draw() const
{
    int i, j;
    	
    attron(COLOR_PAIR(13));
    
    for(i=0;i<height;i++){
	for(j=0;j<width;j++)
	    mvaddch(top+i, left+j, ' ');
    }
    attroff(COLOR_PAIR(13));
}

