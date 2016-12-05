/** @package Snake
* @file Snake.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_SNAKE
#define ANNA_SNAKE

#include "Apple.h"

class Snake
{
private:
    char headChar;
    char bodyChar;
    
public:
    int length;
    int* x;
    int* y;

    Snake(int length_in = 5, int xSatrt = 10, int yStart = 10);///@param x, y - position of head
    ~Snake();
    
    void draw() const;
    void newCoordinates (int arrowKey);
    bool collisionDetection();
    
    int headDirection();
    int tailDirection();
    void changeLength(int newLength);
    void eatApple(Apple::Type appleType);
};

#endif