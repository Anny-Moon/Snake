/* Copyright 2017 Anna Sinelnikova
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
*/

/** @package Snake
* @file Obstacle.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_OBSTACLE
#define SNAKE_OBSTACLE

#include <ncurses.h>

class Obstacle
{
private:
    
public:
    /** The size of game space */
    int height;
    int width;
    int xStart;//< top left corner
    int yStart;//< top left corner
    
    int N;//<number of elements in odstacle
    int* x;//< coordinates of walls
    int* y;//<coordinates of walls
    
    int top; //< x top border
    int bottom; //< x bottom border
    int left; //< y lefth border
    int right; // y rigth border
    
    Obstacle();
    Obstacle(const Obstacle& o);
    void init(int width_in, int height_in, int xStart_in, int yStart_in);
    ~Obstacle();
    
    void draw() const;
    
    inline int getN() const;
    inline int getX(int i) const;
    inline int getY(int i) const;
    
    static bool isPixelFree(int x, int y, const Obstacle* obstacle, int numObstacles);
    
    Obstacle& operator=(const Obstacle& o){
	if(this!=&o){
	    width = o.width;
	    height = o.height;
	    xStart = o.xStart;
	    yStart = o.yStart;
    
	    top = o.top;
	    bottom = o.bottom;
	    left = o.left;
	    right = o.right;
    
	    N = o.N;
	    x = new int[N];
	    y = new int[N];
	    for(int i=0;i<N;i++){
		x[i] = o.x[i];
		y[i] = o.y[i];
	    }
	}
	return *this;
    }
};

inline int Obstacle::getN() const
{
    return N;
}

inline int Obstacle::getX(int i) const
{
    return x[i];
}

inline int Obstacle::getY(int i) const
{
    return y[i];
}

#endif