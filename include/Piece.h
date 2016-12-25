/** @package Snake
* @file Piece.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_PIECE
#define ANNA_PIECE

#include "Box.h"

class Piece
{
private:
    
public:
    char pieceChar;
    int colorScheme;
    
    double x;
    double y;
    
    int intX;
    int intY;
    
    double velocityX;
    double velocityY;
    
    double accelerationX;
    double accelerationY;
    
    double time;
    const Box* box;

    
    Piece(double x0, double y0, double vx0, double vy0, double ax0 = 0.0, double ay0 = 0.0, const Box* box_in = NULL, double time0 = 0.0);
    Piece();
    ~Piece();
    
    void setBox(const Box* box);
    int rounding(double number);
    int findIntX();
    int findIntY();
    void findCoordinates(double time, const int* xObst = NULL, const int* yObst = NULL, int N=0);//< arrays of odstacle coordinates
    void erase() const;
    void draw() const;
};

#endif