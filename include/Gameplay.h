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
#include "Speed.h"
#include "Piece.h"


class Gameplay
{

public:
//    static int dTime; //< time delay in msec

    static void printLogo(int y, int x);
    static void gameover(const Snake* snake, const Box* box);
    static void gameLoop(Snake* snake, RunningApple* apple, Box* box, Score* score, Speed* speed, int ch);
/*   
    //in version v3.0
    static void gameLoopWithBonus(Snake* snake, RunningApple* apple, RunningApple* bonus, Box* box, Score* score, int ch);
    
    //in version v2.0
    static void gameLoopForTwo(Snake* snake, Snake* snake2, RunningApple* apple, Box* box, Score* score, Score* score2, int ch);
*/
};

#endif