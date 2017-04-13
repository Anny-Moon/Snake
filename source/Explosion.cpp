/** @package Snake
* @file Explosion.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Explosion.h"
#include <ncurses.h>
#include <math.h>
#include <stdlib.h> // for random

Explosion::Explosion(int numPieces_in, const int* x_in, const int* y_in, const Box* box_in, double time_in)
{
    int i;
    
    time = time_in;
    box = box_in;
    numPieces = numPieces_in-1;
    

    velocityX = new double [numPieces];
    velocityY = new double [numPieces];
    accelerationX = new double [numPieces];
    accelerationY = new double [numPieces];
    
    x = new int [numPieces];
    y = new int [numPieces];
    for(i=0;i<numPieces;i++){
	x[i] = x_in[i+1];
	y[i] = y_in[i+1];
    }
    
    piece = new Piece [numPieces];
    for(i=0;i<numPieces;i++){
	piece[i].x = (double) x[i];
	piece[i].y = (double) y[i];
	piece[i].time = time_in;
	piece[i].setBox(box);
    }
    
}

Explosion::~Explosion()
{	
    delete [] x;
    delete [] y;
    delete [] velocityX;
    delete [] velocityY;
    delete [] accelerationX;
    delete [] accelerationY;
    
    delete [] piece;
}

void Explosion::setPhysics()
{
    int i;
    
    for(i=0;i<numPieces;i++){
	velocityX[i] = ((double)rand() / (double)RAND_MAX-0.5) /30;
	velocityY[i] = ((double)rand() / (double)RAND_MAX-0.5) /30;
//	velocityX[i] = 0.02;
//	velocityY[i] = 0.01;
	accelerationX[i] = -0.000003 * velocityX[i]/fabs(velocityX[i]);
	accelerationY[i] = -0.000003 * velocityY[i]/fabs(velocityY[i]);
	
//	accelerationX[i] = -0.00001;
//	accelerationY[i] = -0.00001;
	
	piece[i].velocityX = velocityX[i];
    	piece[i].velocityY = velocityY[i];
    	piece[i].accelerationX = accelerationX[i];
    	piece[i].accelerationY = accelerationY[i];
    }

}

void Explosion::findCoordinates(double time_in,  const int* xObst, const int* yObst, int N)
{
    int i;
    time = time_in;
//    mvprintw(31,60,"%g",time);
/*    int* xOthers;
    int* yOthers;
    
    for(i=0;i<numPieces;i++){
	xOthers = new int [numPieces-1];
	yOthers = new int [numPieces-1];
	
	for(j=0;j<i;j++){
	    xOthers[j] = x[j];
	    yOthers[j] = x[j];
	}
	
	for(j=i+1;j<numPieces;j++){
	    xOthers[j-1] = x[j];
	    yOthers[j-1] = x[j];
	}
	
	piece[i].findCoordinates(time, xOthers,yOthers, numPieces-1);
	
	delete [] xOthers;
	delete [] yOthers;
    }
*/
    for(i=0;i<numPieces;i++)
	piece[i].findCoordinates(time, xObst,yObst, N);

//    mvprintw(25,60,"%g",velocityX[0]);
//    mvprintw(28,60,"%g",piece[0].velocityX);

}

void Explosion::erase() const
{
    int i;
    for(i=0;i<numPieces;i++){
	piece[i].erase();
    }

}

void Explosion::draw() const
{
    int i;
        piece[0].pieceChar = 'L';
        piece[1].pieceChar = 'S';
        piece[2].pieceChar = 'E';
        piece[3].pieceChar = 'R';
        
    for(i=0;i<numPieces;i++){
	piece[i].draw();
    }
}