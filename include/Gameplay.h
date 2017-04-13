/* Copyright 2017 Anna Sinelnikova
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
*/

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