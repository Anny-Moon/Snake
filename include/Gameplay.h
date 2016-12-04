/** @package Snake
* @file Gameplay.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_GAMEPLAY
#define ANNA_GAMEPLAY

#include "Snake.h"

class Gameplay
{
public:
    static void gameLoop(Snake* snake, int ch);
    static int kbhit();
};

#endif