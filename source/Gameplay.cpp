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

void Gameplay::printLogo(int y, int x)
{
    attron(COLOR_PAIR(11));
    mvprintw(y, x, " .. .   ..    _    _  .   _._");
    mvprintw(y+1,x,"/ / |\\  ||  / . | | |//  |  _|");
    mvprintw(y+2,x,"\\ \\ |  \\|| |  _ | |   \\  |  _");
    mvprintw(y+3,x,"/_/ |_|\\_| |_| || |_|\\_\\ |___|");
    attroff(COLOR_PAIR(11));
}

void Gameplay::gameLoop(Snake* snake, RunningApple* apple, Box* box, Score* score, Speed* speed, int ch)
{
    time_t initialTime, currentTime;
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber;
    int latestCh = ch;
    
    int absoluteTime = 0;
    
    if(ch == 'q' || ch == 'Q')
	return;
    printLogo(box->bottom+2,box->left+10);
    
    box->draw();
    snake->draw();
    apple->draw();
    score->draw();
    speed->draw();
    printLogo(box->bottom+2,box->left+10);
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box->left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    move(0, 0);// move cursor
    refresh();
    
    initialTime = time(NULL);
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    
    for(;;){
	currentTime = time(NULL);
	absoluteTime += 1;
//	mvprintw(40,35,"%d", absoluteTime);
	
	if(apple->eatingDetection(snake->x[0], snake->y[0])){
	    appleCounter++;
	    snake->erase();
	    apple->erase();
	
	    score->calculatePoints(points);
	    
	    snake->eatApple(Apple::normal);
	    if(appleCounter%10==0 && snake->dTime > 3000){
		snake->dTime-=(int)(snake->dTime*0.25);
		speed->points+=1;
	    }
		
	    score->draw();
	    speed->draw();
	    snake->draw();

	    randomNumber = rand()%2;
	    
	    if(randomNumber == 0){
		apple->newRunningApple((double)absoluteTime, 20000, 20000);
		points = 20;
	    }
	    
	    else{
		apple->newStableApple();
		points = 10;
	    }
	    apple->draw();
//	    mvprintw(10,60,"%d %d", apple->intX, apple->intY);
//	    mvprintw(11,60,"%g %g", apple->x,apple->y);
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
	    napms(100);
	    apple->erase();
	    Explosion explosion(snake->length, snake->x, snake->y, box);
	    explosion.setPhysics();
	    explosion.findCoordinates(0.0, NULL,NULL,0);
	    explosion.draw();
	    int t=0;
	    
	    attron(COLOR_PAIR(10));
	    attron(A_BLINK);
	    mvprintw(3, 21,"press 'q' to quite");
	    attroff(A_BLINK);
	    attroff(COLOR_PAIR(10));
	    
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
//	napms(1);
    }
    
}
/*
void Gameplay::gameLoopWithBonus(Snake* snake, RunningApple* apple, RunningApple* bonus, Box* box, Score* score, int ch)
{
    int appleCounter = 0;
    int points = 10; // the first apple
    int randomNumber, randomNumber2;
    int latestCh = ch;
    
    int bonusTime = 0;
    int bonusDtime = 10;
    int bonusPoints = 0;
    
    unsigned int absoluteTime = 0;
    bool bonusOnScreen = false;
    
    if(ch == 'q' || ch == 'Q')
	return;
    printLogo(box->bottom+2,box->left+10);
    
    box->draw();
    snake->draw();
    apple->draw();
    score->draw();
    
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box->left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    move(0, 0);// move cursor
    refresh();
    
    for(;;){
	absoluteTime += 1;
	
	randomNumber2 = rand()%1000000;// for bonus
//	mvprintw(30,70,"%i",randomNumber2);
	if(randomNumber2 == 0 && bonusOnScreen == false)
//	if(absoluteTime ==1)
	{
	    bonus->newRunningApple(7000, 7000);
	    bonus->setAsBonus(RunningApple::money);
	    bonus->draw();
	    bonusOnScreen = true;
	    bonusTime = 0;
	    bonusPoints = bonus->cost;
	}
	bonusTime++;
	    
	if(bonusOnScreen && bonusTime < 1000000){
	    bonus->erase();
	    bonus->findCoordinates((double)absoluteTime, snake->x, snake->y, snake->length);
	    if(bonus->intX == apple->intX && bonus->intY == apple->intY)//if bonus erase apple
		apple->draw();
	    bonus->draw();
	    move(0, 0);
	    refresh();
	}

	else{
	    bonus->erase();
	    bonus->findCoordinates((double)absoluteTime, snake->x, snake->y, snake->length);
	    bonus->move(0,0);
	    bonus->draw();
	    move(0, 0);
	    refresh();
	}
	
	if(bonus->eatingDetection(snake->x[0], snake->y[0])){
	    bonus->erase();
	    bonus->move(0,0);
	    bonusOnScreen = false;
	    snake->erase();
	    score->calculatePoints(bonusPoints);
	    score->draw();
	    snake->eatApple(Apple::nothing);
	    snake->draw();
	    move(0,0);
	}
	
	if(apple->eatingDetection(snake->x[0], snake->y[0])){
	    appleCounter++;
	    snake->erase();
	    apple->erase();
	
	    score->calculatePoints(points);
	    
	    snake->eatApple(Apple::normal);
	    score->draw();
	    snake->draw();

	    randomNumber = rand()%3;
	    
	    if(randomNumber == 0){
		apple->newRunningApple(20000, 20000);
		apple->cost = 20;
	    }
	    
	    else{
		apple->newStableApple();
	    }
	    
	    points = apple->cost;
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
	    apple->draw();
	    snake->draw();
	    
	    move(0, 0); // move cursor
	    refresh();
	}
	
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
	    return;
	}
	
	latestCh = ch;
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
    printLogo(box->bottom+2,box->left+10);
    box->draw();
    snake->draw();
    snake2->draw();
    apple->draw();
    score->draw();
    score2->draw();
    
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box->left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
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
		apple->newRunningApple(20000, 20000);
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
*/