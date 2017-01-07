/** @package Snake
* @file Obstacle.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_OBSTACLE
#define SNAKE_OBSTACLE

#include <ncurses.h>

class Obstacle
{
private:
    
public:
    /** The size of game space */
    int height;
    int width;
    int xStart;//< top left corner
    int yStart;//< top left corner
    
    int N;//<number of elements in odstacle
    int* x;//< coordinates of walls
    int* y;//<coordinates of walls
    
    int top; //< x top border
    int bottom; //< x bottom border
    int left; //< y lefth border
    int right; // y rigth border
    
    Obstacle();
    void init(int width_in, int height_in, int xStart_in, int yStart_in);
    ~Obstacle();
    
    void draw() const;
};

#endif