/** @package Snake
* @file Box.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Box.h"
#include <ncurses.h>

Box::Box(int width_in, int height_in, int xStart_in, int yStart_in)
{
    width = width_in;
    height = height_in;
    xStart = xStart_in;
    yStart = yStart_in;
    
    top = yStart;
    bottom = yStart + height - 1;
    left = xStart;
    right = xStart + width - 1;
}

Box::~Box(){}

void Box::draw() const
{
    int i;
    	
//    attron(COLOR_PAIR(2));
    for(i=left;i<=right;i++){
	mvaddch(top-1, i, '_');
	mvaddch(bottom+1, i, '^');
    }
    
    for(i=top;i<=bottom;i++){
	mvaddch(i, left-1, '|');
	mvaddch(i, right+1, '|');
    }
//    attroff(COLOR_PAIR(2));
}

