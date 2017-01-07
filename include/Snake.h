/** @package Snake
* @file Snake.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_SNAKE
#define ANNA_SNAKE

#include "Apple.h"
#include "Box.h"
#include "Obstacle.h" //for collosionDetection with obstacles

class Snake
{
private:
    char headChar;
    char bodyChar;
    
public:
    int length;
    int* x;
    int* y;
    
    int dTime;//< delay in msec
    
    int keyboardMode;//< for multiplayer
    int colorScheme;
    
    Snake(int length_in = 5, int xSatrt = 10, int yStart = 10, int dTime_in = 100);///@param x, y - position of head
    ~Snake();
    
    void erase() const;
    void draw() const;
    void newCoordinates (int arrowKey);
    bool collisionDetection(const Box& box);
    bool collisionDetection(const Obstacle* obstacle, int N);//<collision with obtacles;
    int headDirection();
    int tailDirection();
    void changeLength(int newLength);
    void eatApple(Apple::Type appleType);
};

#endif