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

void Gameplay::gameLoop(Snake* snake, RunningApple* apple, Box* box, Score* score, int ch)
{
    time_t initialTime, currentTime;
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
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
	
	if(apple->eatingDetection(snake->x[0], snake->y[0])){
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
	apple->findCoordinates((double)absoluteTime, snake->x, snake->y, snake->length);
	apple->draw();
	move(0, 0);
	refresh();
	
	if(ch == ERR)
	    ch = latestCh;
	
	if(absoluteTime%snake->dTime == 0){
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
//	}
	
	if(ch == 'q' || ch == 'Q')
	    break;
	
	if(snake->collisionDetection(*box))
	{
	    beep();
	    napms(50);
	    apple->erase();
	    Explosion explosion(snake->length, snake->x, snake->y, box);
	    explosion.setPhysics();
	    explosion.findCoordinates(0.0, NULL,NULL,0);
	    explosion.draw();
	    int t=0;
	    for(;;){
		
		ch = getch();
		if(ch == 'q' || ch == 'Q')
		    break;
		explosion.erase();
		explosion.findCoordinates((double)t, NULL,NULL,0);
		explosion.draw();
		move(0,0);
		refresh();
		napms(1);
		t++;
	    }
	    /*
	    clear();
	    attron(COLOR_PAIR(2));
	    //mvprintw(2, 4,"Try next time!");
	    score->draw();
	    move(0,0);
	    refresh();
	    napms(2000);
	    */
	    return;
	}
	
	latestCh = ch;
	napms(1);
    }
    
}

void Gameplay::gameLoopForTwo(Snake* snake, Snake* snake2, RunningApple* apple, Box* box, Score* score, Score* score2, int ch)
{
    time_t initialTime, currentTime;
    int j;
    int appleCounter = 0, length;
    int *xObst, *yObst;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
    int absoluteTime = 0;
    
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    box->draw();
    snake->draw();
    snake2->draw();
    apple->draw();
    score->draw();
    score2->draw();
    move(0, 0);// move cursor
    refresh();
    
    initialTime = time(NULL);
    for(;;){
	currentTime = time(NULL);
	absoluteTime += 1;
	
	if(apple->eatingDetection(snake->x[0], snake->y[0])){
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
	
	if(apple->eatingDetection(snake2->x[0], snake2->y[0])){
	    appleCounter++;
	    snake2->erase();
	    apple->erase();
	
	    score2->calculatePoints(points);
	    
	    snake2->eatApple(Apple::normal);
	    score2->draw();
	    snake2->draw();
	
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
	
		if(ch == 'q' || ch == 'Q')
	    break;
//apple move
	length = snake->length + snake2->length;
	xObst = new int [length];
	yObst = new int [length];
	
	for(j=0;j<snake->length;j++){
	    xObst[j] = snake->x[j];
	    yObst[j] = snake->y[j];
	}
	
	for(j=0;j<snake2->length;j++){
	    xObst[j+snake->length] = snake2->x[j];
	    yObst[j+snake->length] = snake2->y[j];
	}
	apple->erase();
	apple->findCoordinates((double)absoluteTime, xObst, yObst, length);
	apple->draw();
	move(0, 0);
	refresh();
	delete [] xObst;
	delete [] yObst;
	
	if(ch == ERR)
	    ch = latestCh;

//first Snake move
	
	if(absoluteTime%snake->dTime == 0){
	    snake->erase();
	    snake->newCoordinates(ch);
	    apple->draw();
	    snake->draw();
	    
	    move(0, 0); // move cursor
	    refresh();
	}
	
//second Snake move
	if(absoluteTime%snake2->dTime == 0){
	    snake2->erase();
	    snake2->newCoordinates(ch);
	    //apple->draw();
	    snake2->draw();
	    
	    move(0, 0); // move cursor
	    refresh();
	}
	
// 1st Snake 
	if(snake->collisionDetection(*box)|| snake->collisionDetection(snake2->x, snake2->y, snake2->length))
	{
	    beep();
	    napms(50);
	    apple->erase();
	    Explosion explosion(snake->length, snake->x, snake->y, box);
	    explosion.setPhysics();
	    explosion.findCoordinates(0.0, snake2->x, snake2->y, snake2->length);
	    explosion.draw();
	    int t=0;
	    for(;;){
		
		ch = getch();
		if(ch == 'q' || ch == 'Q')
		    break;
		explosion.erase();
		explosion.findCoordinates((double)t, snake2->x, snake2->y, snake2->length);
		explosion.draw();
		move(0,0);
		refresh();
		napms(1);
		t++;
	    }
	    return;
	}
// 2nd Snake
	if(snake2->collisionDetection(*box) || snake2->collisionDetection(snake->x, snake->y, snake->length))
	{
	    beep();
	    napms(50);
	    apple->erase();
	    Explosion explosion(snake2->length, snake2->x, snake2->y, box);
	    explosion.setPhysics();
	    explosion.findCoordinates(0.0, snake->x, snake->y, snake->length);
	    explosion.draw();
	    int t=0;
	    for(;;){
		
		ch = getch();
		if(ch == 'q' || ch == 'Q')
		    break;
		explosion.erase();
		explosion.findCoordinates((double)t,snake->x, snake->y, snake->length);
		explosion.draw();
		move(0,0);
		refresh();
		napms(1);
		t++;
	    }
	    return;
	}
	latestCh = ch;
	napms(1);
    }

}