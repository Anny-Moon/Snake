/** @package Snake
* @file Speed.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Speed.h"
#include <ncurses.h>

Speed::Speed(int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    points = 1;
    
}

Speed::~Speed(){}


void Speed::calculatePoints(int points_in)
{
    points += points_in;
}

void Speed::draw() const
{
    int i;
    mvprintw(y, x, "Speed: %i",points);
}

