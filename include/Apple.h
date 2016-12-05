/** @package Snake
* @file Apple.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_APPLE
#define ANNA_APPLE


class Apple
{
private:
    char appleChar;
    
public:
    int x;
    int y;
    
    enum Type{normal};//< different bonuses
    
    Apple(int x_in, int y_in, char ch);
    ~Apple();
    
    void draw() const;
    void newCoordinates ();
    bool collisionDetection(int xSnake, int ySnake);
};

#endif