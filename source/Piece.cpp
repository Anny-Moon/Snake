#include "../include/Piece.h"
#include <math.h>

Piece::Piece(double x0, double y0, double vx0, double vy0, double ax0, double ay0, const Box* box_in, double time0)
{
    pieceChar = 'O';
    colorScheme = 3;
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

Piece::Piece()
{
    pieceChar = 'O';
    colorScheme = 3;
}

Piece::~Piece(){};

void Piece::setBox(const Box* box_in)
{
    box = box_in;
}
void Piece::findCoordinates(double time_in,const  int* xObst, const int* yObst, int N)
{	
    int i, k;
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

    if(xObst!=NULL){ // collisions with snake
	for(i=0;i<N;i++){
	
	    if(intX == xObst[i]-1 && intY == yObst[i] && velocityX > 0){ // left->right - along x axis
		x = (double)intX;
		velocityX = -velocityX;
		accelerationX = -accelerationX;
		x = x + velocityX * dt;
		break;
	    }
	
	    if(intX == xObst[i]+1 && intY == yObst[i] && velocityX < 0){ // right->left - along x axis
		x = (double)intX;
		velocityX = -velocityX;
		accelerationX = -accelerationX;
		x = x + velocityX * dt;
		break;
	    }
	
	    if(intY == yObst[i]-1 && intX == xObst[i] && velocityY > 0){ // top->bottom - along y axis
		y = (double)intY;
		velocityY = -velocityY;
		accelerationY = -accelerationY;
		y = y + velocityY * dt;
		break;
	    }
	
	    if(intY == yObst[i]+1 && intX == xObst[i] && velocityY < 0){ // bottom->top - along y axis
		y = (double)intY;
		velocityY = -velocityY;
		accelerationY = -accelerationY;
		y = y + velocityY * dt;
		break;
	    }
    
    }
	intX = findIntX();
	intY = findIntY();
    }
    
    if(obstacle != NULL){ // collisions with obstacle
	for(k=0;k<numObstacles;k++){
	    for(i=0;i<obstacle[k].N;i++){
		    if(intX == obstacle[k].x[i]-1 && intY == obstacle[k].y[i] && velocityX > 0){ // left->right - along x axis
			x = (double)intX;
			velocityX = -velocityX;
			accelerationX = -accelerationX;
			x = x + velocityX * dt;
			break;
		    }
		
		    if(intX == obstacle[k].x[i]+1 && intY == obstacle[k].y[i] && velocityX < 0){ // right->left - along x axis
			x = (double)intX;
			velocityX = -velocityX;
			accelerationX = -accelerationX;
			x = x + velocityX * dt;
			break;
		    }
		
		    if(intY == obstacle[k].y[i]-1 && intX == obstacle[k].x[i] && velocityY > 0){ // top->bottom - along y axis
			y = (double)intY;
			velocityY = -velocityY;
			accelerationY = -accelerationY;
			y = y + velocityY * dt;
		    break;
		}
		
		    if(intY == obstacle[k].y[i]+1 && intX == obstacle[k].x[i] && velocityY < 0){ // bottom->top - along y axis
			y = (double)intY;
			velocityY = -velocityY;
			accelerationY = -accelerationY;
			y = y + velocityY * dt;
			break;
		    }
	
	    }
	}
	intX = findIntX();
	intY = findIntY();
    }
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
//    mvprintw(40,40,"%g",velocityX);
//    mvprintw(41,40,"%g",velocityY);
    
    attron(COLOR_PAIR(colorScheme));
    mvaddch(intY, intX, pieceChar);
    attroff(COLOR_PAIR(colorScheme));
}
