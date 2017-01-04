/** @package Snake
* @file RunningApple.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_RUNNING_APPLE
#define ANNA_RUNNING_APPLE

#include "Box.h"
#include "Piece.h"

class RunningApple : public Piece
{
private:
public:
    
    enum Type{normal, money};//< different bonuses
    Type type;
    int cost;
    
    RunningApple(const Box* box_in, char ch = '#', Type type_in = normal);
    ~RunningApple();
    void move(int intX_in, int intY_in);
    
    void newStableApple();
    void newRunningApple(double time0, int maxXspeed = 20000, int maxYspeed = 20000);
    void setAsBonus(Type type);
    bool eatingDetection(int xSnake, int ySnake);
};

#endif