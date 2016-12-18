/** @package Snake
* @file Score.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Score.h"
#include <ncurses.h>

Score::Score(int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    points = 0;
    
}

Score::~Score(){}

void Score::calculatePoints(const Apple& apple)
{
    switch (apple.type){
	case Apple::normal:
	points += 10;
	break;
    
    }
}

void Score::draw() const
{
    int i;
    mvprintw(y, x, "Score: %i",points);
}

