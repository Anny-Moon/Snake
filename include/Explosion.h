/** @package Snake
* @file Explosion.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_EXPLOSION
#define ANNA_EXPLOSION

#include "Box.h"
#include "Piece.h"

class Explosion
{
private:
    int numPieces;
    Piece* piece;
    double time;
public:
    int* x;
    int* y;
    const Box* box;
    
    double* velocityX;
    double* velocityY;
    double* accelerationX;
    double* accelerationY;
    
    Explosion(int numPieces_in, const int* x_in, const int* y_in, const Box* box_in, double time0 = 0.0);
    ~Explosion();
    
    void setPhysics(); //< set velocities and accelerations
    void findCoordinates(double time_in, const int* xObst, const int* yObst, int N);
        
    void erase() const;
    void draw() const;
};

#endif