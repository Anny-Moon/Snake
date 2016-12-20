/** @package Snake
* @file Gameplay.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_GAMEPLAY
#define ANNA_GAMEPLAY

#include "Snake.h"
#include "RunningApple.h"
#include "Box.h"
#include "Score.h"
#include "Piece.h"


class Gameplay
{

public:
//    static int dTime; //< time delay in msec

    static void gameLoop(Snake* snake, RunningApple* apple, Box* box, Score* score, Piece* piece, int ch);
};

#endif