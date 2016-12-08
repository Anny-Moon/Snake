/** @package Snake
* @file Gameplay.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_GAMEPLAY
#define ANNA_GAMEPLAY

#include "Snake.h"
#include "Apple.h"
#include "Box.h"
#include "Score.h"
class Gameplay
{
public:
    static void gameLoop(Snake* snake, Apple* apple, Box* box, Score* score, int ch);
};

#endif