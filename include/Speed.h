/** @package Snake
* @file Speed.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_SPEED
#define SNAKE_SPEED

#include <ncurses.h>

class Speed
{
private:
public:
    int points;
    int x;
    int y;
    
    Speed(int x_in, int y_in);
    ~Speed();
    
    void calculatePoints(int points_in);
    void draw() const;
};

#endif