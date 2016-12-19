#include "../include/Piece.h"
#include <math.h>

Piece::Piece(double x0, double y0, double vx0, double vy0, double ax0, double ay0, const Box* box_in, double time0)
{
    pieceChar = 'O';
    x = x0;
    y = y0;
    velocityX = vx0;
    velocityY = vy0;
    accelerationX = ax0;
    accelerationY = ay0;
    box = box_in;
    time = time0;
    
    if (box!=NULL){
	intX = findIntX();
	intY = findIntY();
    }
}

Piece::~Piece(){};


void Piece::findCoordinates(double time_in)
{
    double tmp;
    double dt = time_in-time;
    time = time_in;

    tmp = velocityX;
    velocityX = velocityX + accelerationX*dt;
    if(tmp*velocityX<0.0){
        velocityX = 0.0;
    	accelerationX = 0.0;
    }
    
    tmp = velocityY;
    velocityY = velocityY + accelerationY*dt;
    if(tmp*velocityY<0.0){
        velocityY = 0.0;
    	accelerationY = 0.0;
    }

    x = x + velocityX * dt;
    y = y + velocityY * dt;
    
    if(x < box->left || x > box->right){ //reflection from the boders of the box
	velocityX = -velocityX;
	accelerationX = -accelerationX;
	x = x + velocityX * dt;
    }
    
    if(y < box->top || y > box->bottom){ //reflection from the boders of the box
	velocityY = -velocityY;
	accelerationY = -accelerationY;
	y = y + velocityY * dt;
	
    }
    
    intX = findIntX();
    intY = findIntY();
}

int Piece::rounding(double number)
{
    double intpart;
    double fracpart;
    int answ;

    fracpart=modf (number , &intpart);

    if(fabs(fracpart)<0.499999)
	answ=(int)intpart;
    
    else
	answ=(int)intpart+1;
    
    return answ;
}


int Piece::findIntX()
{
    return rounding(x);
}

int Piece::findIntY()
{
    return rounding(y);
}

void Piece::erase() const
{
    mvaddch(intY, intX, ' ');
}
void Piece::draw() const
{	
    attron(COLOR_PAIR(1));
    mvaddch(intY, intX, pieceChar);
    attroff(COLOR_PAIR(1));
}