/** @package Snake
* @file Box.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_BOX
#define SNAKE_BOX

#include <ncurses.h>

class Box
{
private:
    
public:
    /** The size of game space */
    int height;
    int width;
    int xStart;//< top left corner
    int yStart;//< top left corner
    
    int top; //< x top border
    int bottom; //< x bottom border
    int left; //< y lefth border
    int right; // y rigth border
    
    Box(int width_in, int height_in, int xStart_in, int yStart_in);
    ~Box();
    
    void draw() const;
};

#endif