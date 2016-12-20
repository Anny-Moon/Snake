/** @package Snake
* @file Gameplay.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Gameplay.h"
#include "Explosion.h"
#include <ncurses.h>
#include <time.h>

void Gameplay::gameLoop(Snake* snake, Apple* apple, Box* box, Score* score, Piece* piece, int ch)
{
    time_t initialTime, currentTime;
    int latestCh = ch;
    
    int dTime = 100;
    double absoluteTime = 0.0;
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    // Show the main character on the screen

    box->draw();
    snake->draw();
    apple->draw();
    score->draw();
    
//    piece->draw();    
    move(0, 0);// move cursor
    refresh();
    
    for(;;){
//	initialTime = time(NULL);
//	currentTime = time(NULL);
	absoluteTime += (double)dTime;
//	piece->erase();
//	piece->findCoordinates(absoluteTime);
//	piece->draw();
	move(0, 0);// move cursor
	
	if(apple->collisionDetection(snake->x[0], snake->y[0])){
	    snake->eatApple(Apple::normal);
	    apple->newCoordinates(*box);
	    score->calculatePoints(*apple);
	    erase();
	    box->draw();
	    apple->draw();
	    snake->draw();
	    score->draw();
	    

	    move(0, 0);// move cursor
	    refresh();
	}
	
	timeout(0);
    	ch = getch();
	
	//while(difftime(currentTime,initialTime)<0.5){
	//    currentTime = time(NULL);
	//    if(ch != ERR)
	//	break;
	//}
	
	if(ch == ERR)
	    ch = latestCh;
	
	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN){
	    snake->newCoordinates(ch);
	    erase();
	    box->draw();
	    apple->draw();
	    snake->draw();
	    score->draw();
	    
//	    piece->draw();
	    move(0, 0); // move cursor
	    refresh();
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
	//pause 
	napms(dTime);
    }
    
}

