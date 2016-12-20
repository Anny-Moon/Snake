/** @package Snake
* @file Gameplay.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Gameplay.h"
#include "Explosion.h"
#include <stdlib.h> //for rand 
#include <ncurses.h>
#include <time.h>

void Gameplay::gameLoop(Snake* snake, RunningApple* apple, Box* box, Score* score, Piece* piece, int ch)
{
    time_t initialTime, currentTime;
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
    int dTime = 100;
    int absoluteTime = 0;
    
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    box->draw();
    snake->draw();
    apple->draw();
    score->draw();
    move(0, 0);// move cursor
    refresh();
    
    initialTime = time(NULL);
    for(;;){
	currentTime = time(NULL);
	absoluteTime += 1;
	
	if(apple->collisionDetection(snake->x[0], snake->y[0])){
	    appleCounter++;
	    snake->erase();
	    apple->erase();
	
	    score->calculatePoints(points);
	    
	    snake->eatApple(Apple::normal);
	    score->draw();
	    snake->draw();

	    randomNumber = rand()%4;
	    
	    if(randomNumber == 0){
		apple->newRunningApple();
		points = 20;
	    }
	    
	    else{
		apple->newStableApple();
		points = 10;
	    }
	    apple->draw();
	    
	    move(0, 0);// move cursor
	    refresh();
	}
	
	timeout(0);
    	ch = getch();
	
	apple->erase();
	apple->findCoordinates((double)absoluteTime);
	apple->draw();
	move(0, 0);
	refresh();
	
	if(ch == ERR)
	    ch = latestCh;
	
	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN){
	    
	    if(absoluteTime%dTime == 0){
		snake->erase();
		snake->newCoordinates(ch);
		//erase();
		//box->draw();
		apple->draw();
		snake->draw();
		//score->draw();
	    
	    move(0, 0); // move cursor
	    refresh();
	    }
//	    napms(dTime);
	}
	
	else if(ch == 'q' || ch == 'Q')
	    break;
	
	if(snake->collisionDetection(*box))
	{
	    beep();
	    napms(50);
	    Explosion explosion(snake->length, snake->x, snake->y, box);
	    explosion.setPhysics();
	    explosion.findCoordinates(0.0);
	    explosion.draw();
	    int t=0;
	    for(;;){
		
		ch = getch();
		if(ch == 'q' || ch == 'Q')
		    break;
		explosion.erase();
		explosion.findCoordinates((double)t);
		explosion.draw();
		move(0,0);
		refresh();
		napms(1);
		t++;
	    }
	    
	    clear();
	    attron(COLOR_PAIR(2));
	    mvprintw(2, 3,"LOOOOOSER!\n");
	    score->draw();
	    refresh();
	    napms(2000);
	    return;
	}
	
	latestCh = ch;
	napms(1);
    }
    
}

