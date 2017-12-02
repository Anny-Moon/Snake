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
* @file Obstacle.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Obstacle.h"
#include <stdlib.h>
#include <ncurses.h>

Obstacle::Obstacle(){}

Obstacle::Obstacle(const Obstacle& o)
{
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

void Obstacle::init(int width_in, int height_in, int xStart_in, int yStart_in)
{
    int i, j;
    width = width_in;
    height = height_in;
    xStart = xStart_in;
    yStart = yStart_in;
    
    top = yStart;
    bottom = yStart + height - 1;
    left = xStart;
    right = xStart + width - 1;
    
    N = width*height;
    x = new int[N];
    y = new int[N];
    
    for(i=0;i<height;i++){
	for(j=0;j<width;j++){
	    x[i*width+j] = left + j;
	    y[i*width+j] = top + i;
	}
    }
}

Obstacle::~Obstacle()
{
    if(x != NULL)
	delete [] x;
    
    if(y != NULL)
    delete [] y;
}

void Obstacle::draw() const
{
    int i, j;
    	
    attron(COLOR_PAIR(13));
    
    for(i=0;i<height;i++){
	for(j=0;j<width;j++)
	    mvaddch(top+i, left+j, ' ');
    }
    attroff(COLOR_PAIR(13));
}

bool Obstacle::isPixelFree(int x, int y, const Obstacle* obstacle, int numObstacles)
{
    for(int k=0;k<numObstacles;k++){
	for(int i=0;i<obstacle[k].getN();i++){
	    if(x == obstacle[k].getX(i) && y == obstacle[k].getY(i))
		return false;
	}
    }
    return true;
}

bool Obstacle::isPixelFree(int x, int y, const std::vector<Obstacle>& obstacle)
{
    for(int k=0;k<obstacle.size();k++){
	for(int i=0;i<obstacle[k].getN();i++){
	    if(x == obstacle[k].getX(i) && y == obstacle[k].getY(i))
		return false;
	}
    }
    return true;
}

void Obstacle::writeInFile(FILE* fp, const std::vector<Obstacle>& obstacle)
{
    if(fp==NULL){
	endwin();
	printf("Error: problem with writing to the file.\n");
	exit(1);
    }
    
    fprintf(fp, "OBSTACLES\n");
    for(int k=0;k<obstacle.size();k++){
	fprintf(fp,"%i\t%i\t%i\t%i\n", obstacle[k].width,obstacle[k].height,obstacle[k].xStart,obstacle[k].yStart);
    }
    fprintf(fp, "END\n");
}