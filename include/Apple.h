/** @package Snake
* @file Apple.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_APPLE
#define ANNA_APPLE

#include "Box.h"

class Apple
{
private:
    char appleChar;
    
public:
    int x;
    int y;
    
    enum Type{normal, running, nothing};//< different bonuses
    Type type;

    Apple(int x_in, int y_in, char ch, Type type_in = normal);
    ~Apple();
    
    void erase() const;
    void draw() const;
    void newCoordinates (const Box& box);
    bool collisionDetection(int xSnake, int ySnake);
};

#endif