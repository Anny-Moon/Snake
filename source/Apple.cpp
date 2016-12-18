/** @package Snake
* @file Apple.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Apple.h"
#include <stdlib.h> // for random
#include <ncurses.h>

Apple::Apple(int x_in, int y_in, char ch, Type type_in)
{
    x = x_in;
    y = y_in;
    appleChar = ch;
    type = type_in;

}

Apple::~Apple(){}

void Apple::draw() const
{	
    attron(COLOR_PAIR(2));
    mvaddch(y, x, appleChar);
    attroff(COLOR_PAIR(2));
}

void Apple::newCoordinates(const Box& box)
{
    x = rand() % box.width + box.left;
    y = rand() % box.height + box.top;
}

bool Apple::collisionDetection(int xSnake, int ySnake)
{
    if(xSnake == x && ySnake == y)
	return true;
	
    return false;
}