#include "../include/Apple.h"
#include <stdlib.h> // for random
#include <ncurses.h>

Apple::Apple(int x_in, int y_in, char ch)
{
    x = x_in;
    y = y_in;
    appleChar = ch;

}

Apple::~Apple(){}

void Apple::draw() const
{	
    attron(COLOR_PAIR(2));
    mvaddch(y, x, appleChar);
    attroff(COLOR_PAIR(2));
}

void Apple::newCoordinates()
{
    x = rand() % 50;
    y = rand() % 30;
}

bool Apple::collisionDetection(int xSnake, int ySnake)
{
    if(xSnake == x && ySnake == y)
	return true;
	
    return false;
}