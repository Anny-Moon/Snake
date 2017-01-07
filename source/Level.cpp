/** @package Snake
* @file Level.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Level.h"
#include "../include/Box.h"
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
		apple.newRunningApple((double)absoluteTime, 20000, 20000);
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
	    apple.erase;
	    Gameplay::gameover(&snake, &box);
	
	    return;
	}
	
	latestCh = ch;
    }
    
}