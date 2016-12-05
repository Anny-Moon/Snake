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
    mvaddch(y, x, appleChar);
}

void Apple::newCoordinates()
{
    x = rand() % 30;
    y = rand() % 50;
}

bool Apple::collisionDetection(int xSnake, int ySnake)
{
    if(xSnake == x && ySnake == y)
	return true;
	
    return false;
}