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
    
    enum Type{normal};//< different bonuses
    Type type;

    RunningApple(const Box* box_in, char ch = '#', Type type_in = normal);
    ~RunningApple();
    
    void newStableApple();
    void newRunningApple();
    
    bool eatingDetection(int xSnake, int ySnake);
};

#endif