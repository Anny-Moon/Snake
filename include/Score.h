/** @package Snake
* @file Score.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_SCORE
#define SNAKE_SCORE

#include "Apple.h"
#include <ncurses.h>

class Score
{
private:
    int points;

public:
    
    int x;
    int y;
    
    Score(int x_in, int y_in);
    ~Score();
    
    void calculatePoints(const Apple& apple);
    void draw() const;
};

#endif