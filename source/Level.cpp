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
* @file Level.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Level.h"
#include "../include/Box.h"
#include "../include/Obstacle.h"
#include "../include/Snake.h"
#include "../include/RunningApple.h"
#include "../include/Apple.h"
#include "../include/Explosion.h"
#include "../include/Score.h"
#include "../include/Speed.h"
#include "../include/Gameplay.h"

#include <stdlib.h> // for random
#include <ncurses.h>
#include <time.h>

#define _QUITE(ch) if(ch == 'q' || ch == 'Q') return;
#define ADJUST_SPEED\
	if(ch == '='){\
	    snake.dTime -=(int)(0.20*snake.dTime);\
	    ch = latestCh;\
	}\
	if(ch == '-'){\
	    snake.dTime +=(int)(0.20*snake.dTime);\
	    ch = latestCh;\
	}

void Level::zero(int ch)
{
    
    // Create all objects for game
    Box box(50, 30 ,5,5);
    Snake snake(5, 20, 30, 20000);
    RunningApple apple(&box,'Q');
    apple.x = 30.0;
    apple.intX = 30;
    apple.y = 30.0;
    apple.intY = 30;
    Score score(6 ,3);
    Speed speed(46 ,3);
    
    time_t initialTime, currentTime;
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
    int absoluteTime = 0;
    
    Gameplay::printLogo(box.bottom+2,box.left+10);
    
    box.draw();
    snake.draw();
    apple.draw();
    score.draw();
    speed.draw();
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box.left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    move(0, 0);// move cursor
    refresh();
    
    initialTime = time(NULL);
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    
    _QUITE(ch);
    
    for(;;){
	currentTime = time(NULL);
	absoluteTime += 1;
//	mvprintw(40,35,"%d", absoluteTime);
	
	if(apple.eatingDetection(snake.x[0], snake.y[0])){
	    appleCounter++;
	    snake.erase();
	    apple.erase();
	
	    score.calculatePoints(points);
	    
	    snake.eatApple(Apple::normal);
	    if(appleCounter%10==0 && snake.dTime > 3000){
		snake.dTime-=(int)(snake.dTime*0.25);
		speed.points+=1;
	    }
		
	    score.draw();
	    speed.draw();
	    snake.draw();

	    randomNumber = rand()%2;
	    
	    if(randomNumber == 0){
		apple.newRunningApple((double)absoluteTime, 20000, 20000);
		points = 20;
	    }
	    
	    else{
		apple.newStableApple();
		points = 10;
	    }
	    apple.draw();
//	    mvprintw(10,60,"%d %d", apple.intX, apple.intY);
//	    mvprintw(11,60,"%g %g", apple.x,apple.y);
	    move(0, 0);// move cursor
	    refresh();
	}
	
	timeout(0);
    	ch = getch();
	
	apple.erase();
	apple.findCoordinates((double)absoluteTime, snake.x, snake.y, snake.length);
	apple.draw();
	move(0, 0);
	refresh();
	
	if(ch == ERR)
	    ch = latestCh;

	if(absoluteTime%snake.dTime == 0){
	    snake.erase();
	    snake.newCoordinates(ch);
	    //erase();
	    //box.draw();
	    apple.draw();
	    snake.draw();
	    //score.draw();
	    
	    move(0, 0); // move cursor
	    refresh();
	}
	
	_QUITE(ch);
		
	if(snake.collisionDetection(box)){
	    apple.erase();
	    Gameplay::gameover(&snake, &box);
	
	    return;
	}
	
	latestCh = ch;
    }
    
}

void Level::one(int ch)
{
    // Create all objects for game
    Box box(25, 15 ,5,5);
    Snake snake(5, 10, 10, 10000);
    RunningApple apple(&box,'Q');
    apple.x = 15.0;
    apple.intX = 15;
    apple.y = 10.0;
    apple.intY = 10;
    Score score(6 ,3);
//    Speed speed(46 ,3);

    int j;
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
    int absoluteTime = 0;
    
    _QUITE(ch);
    
//    Gameplay::printLogo(box.bottom+2,box.left+10);
    attron(COLOR_PAIR(12));
    box.draw();
    attroff(COLOR_PAIR(12));
    
    snake.draw();
    apple.draw();
    score.draw();
//    speed.draw();
    Gameplay::printLogo(box.bottom+2,box.left-3);
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box.left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    move(0, 0);// move cursor
    refresh();
    
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    
    _QUITE(ch);
    
    for(;;){
	absoluteTime += 1;
//	mvprintw(40,35,"%d", absoluteTime);
	
	if(apple.eatingDetection(snake.x[0], snake.y[0])){
	    appleCounter++;
	    snake.erase();
	    apple.erase();
	
	    score.calculatePoints(points);
	    
	    snake.eatApple(Apple::normal);
	    score.draw();
	    snake.draw();

	    randomNumber = rand()%2;
	    
	    if(randomNumber == 0){
		apple.newRunningApple((double)absoluteTime, snake.dTime*2, snake.dTime*2);
		points = 20;
	    }
	    
	    else{
		apple.newStableApple();
		points = 10;
	    }
//	    apple.time = absoluteTime;
//	    mvprintw(10,31,"        ");
//	    mvprintw(10,31,"%d %d", apple.intX, apple.intY);
	    
	    apple.draw();
	    move(0, 0);// move cursor
	    refresh();
	}
	
	timeout(0);
    	ch =getch();
	
	apple.erase();
	apple.findCoordinates((double)absoluteTime, snake.x, snake.y, snake.length);
	
	apple.draw();
	move(0, 0);
	refresh();
	
	if(ch == ERR)
	    ch = latestCh;
	
	ADJUST_SPEED;
		
	if(absoluteTime%snake.dTime == 0){
	    snake.erase();
	    snake.newCoordinates(ch);
	    for(j=0;j<snake.length;j++){
//periodic boundry conditions
		if(snake.x[j] == box.right+1)
		    snake.x[j] = box.left;
		    
		if(snake.x[j] == box.left-1)
		    snake.x[j] = box.right;
		
		if(snake.y[j] == box.bottom+1)
		    snake.y[j] = box.top;    
		    
		if(snake.y[j] == box.top-1)
		    snake.y[j] = box.bottom;
//--------		    
	    }
	    apple.draw();
	    snake.draw();
	    attron(COLOR_PAIR(12));
	    box.draw();
	    attroff(COLOR_PAIR(12));
	    move(0, 0); // move cursor
	    refresh();
	}
	
	_QUITE(ch);
		
	if(snake.collisionDetection(box)){
	    apple.erase();
	    Gameplay::gameover(&snake, &box);
	
	    return;
	}
	
	latestCh = ch;
    }
    
}

void Level::two(int ch)
{
    
    // Create all objects for game
    int numObst = 4;
    Obstacle* obstacle;
    obstacle = new Obstacle [numObst];
    obstacle[0].init(6,3,10,7);
    obstacle[1].init(6,3,29,7);
    obstacle[2].init(6,3,10,20);
    obstacle[3].init(6,3,29,20);
    
    
    Box box(35, 20 ,5,5);
    Snake snake(5, 10, 15, 10000);
    RunningApple apple(&box,'Q',RunningApple::normal,obstacle,numObst);
    apple.x = 15.0;
    apple.intX = 15;
    apple.y = 15.0;
    apple.intY = 15;
    Score score(6 ,3);
//    Speed speed(46 ,3);

    int j;
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
    int absoluteTime = 0;
    
    _QUITE(ch);
    
//    Gameplay::printLogo(box.bottom+2,box.left+10);
    attron(COLOR_PAIR(12));
    box.draw();
    attroff(COLOR_PAIR(12));
    
    for(int k=0;k<numObst;k++)
	obstacle[k].draw();
    snake.draw();
    apple.draw();
    score.draw();
//    speed.draw();
    Gameplay::printLogo(box.bottom+2,box.left+2);
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box.left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    move(0, 0);// move cursor
    refresh();
    
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    
    _QUITE(ch);
    
    for(;;){
	absoluteTime += 1;
//	mvprintw(40,35,"%d", absoluteTime);
	
	    
	if(apple.eatingDetection(snake.x[0], snake.y[0])){
	    appleCounter++;
	    snake.erase();
	    apple.erase();
	
	    score.calculatePoints(points);
	    
	    snake.eatApple(Apple::normal);
	    score.draw();
	    snake.draw();
	    for(int k=0;k<numObst;k++)
		obstacle[k].draw();

	    randomNumber = rand()%2;
	    
	    if(randomNumber == 0){
		apple.newRunningApple((double)absoluteTime, snake.dTime*2, snake.dTime*2);
		points = 20;
	    }
	    
	    else{
		apple.newStableApple();
		points = 10;
	    }
//	    apple.time = absoluteTime;
//	    mvprintw(10,31,"        ");
//	    mvprintw(10,31,"%d %d", apple.intX, apple.intY);
	    
	    apple.draw();
	    move(0, 0);// move cursor
	    refresh();
	}
	
	timeout(0);
    	ch =getch();
	
	apple.erase();
	apple.findCoordinates((double)absoluteTime, snake.x, snake.y, snake.length);
	
	apple.draw();
	move(0, 0);
	refresh();
	
	if(ch == ERR)
	    ch = latestCh;
	
	ADJUST_SPEED;
	
	if(absoluteTime%snake.dTime == 0){
	    snake.erase();
	    snake.newCoordinates(ch);
	    for(j=0;j<snake.length;j++){
//periodic boundry conditions
		if(snake.x[j] == box.right+1)
		    snake.x[j] = box.left;
		    
		if(snake.x[j] == box.left-1)
		    snake.x[j] = box.right;
		
		if(snake.y[j] == box.bottom+1)
		    snake.y[j] = box.top;    
		    
		if(snake.y[j] == box.top-1)
		    snake.y[j] = box.bottom;
//--------		    
	    }
	    apple.draw();
	    snake.draw();
	    attron(COLOR_PAIR(12));
	    box.draw();
	    attroff(COLOR_PAIR(12));
	    move(0, 0); // move cursor
	    refresh();
	}
	
	_QUITE(ch);
		
	if(snake.collisionDetection(box) || snake.collisionDetection(obstacle, numObst)){
	    apple.erase();
	    Gameplay::gameover(&snake, &box);
	
	    return;
	}
	
	latestCh = ch;
    }
    delete [] obstacle;
}

void Level::three(int ch)
{
    
    // Create all objects for game
    int numObst = 2;
    Obstacle* obstacle;
    obstacle = new Obstacle [numObst];
    obstacle[0].init(1,21,25,5);
    obstacle[1].init(41,1,5,15);
    
    
    Box box(41, 21 ,5,5);
    Snake snake(5, 10, 11, 10000);
    RunningApple apple(&box,'Q',RunningApple::normal,obstacle,numObst);
    apple.x = 15.0;
    apple.intX = 15;
    apple.y = 11.0;
    apple.intY = 11;
    Score score(6 ,3);
//    Speed speed(46 ,3);

    int j;
    int appleCounter = 0;
    int points = 10; // the first apple
    int latestCh = ch;
    
    int absoluteTime = 0;
    
    _QUITE(ch);
    
//    Gameplay::printLogo(box.bottom+2,box.left+10);
    attron(COLOR_PAIR(12));
    box.draw();
    attroff(COLOR_PAIR(12));
    
    for(int k=0;k<numObst;k++)
	obstacle[k].draw();
    snake.draw();
    apple.draw();
    score.draw();
//    speed.draw();
    Gameplay::printLogo(box.bottom+2,box.left+6);
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box.left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    move(0, 0);// move cursor
    refresh();
    
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    
    _QUITE(ch);
    
    for(;;){
	absoluteTime += 1;
//	mvprintw(40,35,"%d", absoluteTime);
	
	    
	if(apple.eatingDetection(snake.x[0], snake.y[0])){
	    appleCounter++;
	    snake.erase();
	    apple.erase();
	
	    score.calculatePoints(points);
	    
	    snake.eatApple(Apple::normal);
	    score.draw();
	    snake.draw();
	    for(int k=0;k<numObst;k++)
		obstacle[k].draw();

	    apple.newStableApple();
	    points = 10;
	    
	    apple.draw();
	    move(0, 0);// move cursor
	    refresh();
	}
	
	timeout(0);
    	ch =getch();
	
	apple.erase();
	apple.findCoordinates((double)absoluteTime, snake.x, snake.y, snake.length);
	
	apple.draw();
	move(0, 0);
	refresh();
	
	if(ch == ERR)
	    ch = latestCh;
	
	ADJUST_SPEED;
		
	if(absoluteTime%snake.dTime == 0){
	    snake.erase();
	    snake.newCoordinates(ch);
	    for(j=0;j<snake.length;j++){
//periodic boundry conditions
		if(snake.x[j] == box.right+1)
		    snake.x[j] = box.left;
		    
		if(snake.x[j] == box.left-1)
		    snake.x[j] = box.right;
		
		if(snake.y[j] == box.bottom+1)
		    snake.y[j] = box.top;    
		    
		if(snake.y[j] == box.top-1)
		    snake.y[j] = box.bottom;
//--------		    
	    }
	    apple.draw();
	    snake.draw();
	    attron(COLOR_PAIR(12));
	    box.draw();
	    attroff(COLOR_PAIR(12));
	    move(0, 0); // move cursor
	    refresh();
	}
	
	_QUITE(ch);
		
	if(snake.collisionDetection(box) || snake.collisionDetection(obstacle, numObst)){
	    apple.erase();
	    Gameplay::gameover(&snake, &box);
	
	    return;
	}
	
	latestCh = ch;
    }
    delete [] obstacle;
}