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
* @file Box.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Box.h"
#include "stdlib.h"
#include <ncurses.h>

Box::Box(int width_in, int height_in, int xStart_in, int yStart_in, int boundryConditions_in)
{
    width = width_in;
    height = height_in;
    xStart = xStart_in;
    yStart = yStart_in;
    
    top = yStart;
    bottom = yStart + height - 1;
    left = xStart;
    right = xStart + width - 1;
    
    boundryConditions = boundryConditions_in;
}

Box::~Box(){}

void Box::draw() const
{
    int i;
    	
    if(boundryConditions == 1)
	attron(COLOR_PAIR(12));
    for(i=left;i<=right;i++){
//	mvaddch(top-1, i, '_');
//	mvaddch(bottom+1, i, '^');
	mvaddch(top-1, i, ACS_BLOCK);
	mvaddch(bottom+1, i, ACS_BLOCK);

    }
    
    for(i=top;i<=bottom;i++){
//	mvaddch(i, left-1, '|');
//	mvaddch(i, right+1, '|');
	mvaddch(i, left-1, ACS_BLOCK);
	mvaddch(i, right+1, ACS_BLOCK);
	
    }
    if(boundryConditions == 1)
	attroff(COLOR_PAIR(12));
}

void Box::erase() const
{
    int i;
    	
    for(i=left;i<=right;i++){
	mvaddch(top-1, i, ' ');
	mvaddch(bottom+1, i, ' ');
    }
    
    for(i=top;i<=bottom;i++){
	mvaddch(i, left-1, ' ');
	mvaddch(i, right+1, ' ');
    }
}


void Box::writeInFile(FILE* fp) const
{
    if(fp==NULL){
	endwin();
	printf("Error: problem with writing to the file.\n");
	exit(1);
    }
    
    fprintf(fp,"%i\t%i\t%i\t%i\n", width, height, xStart, yStart);
    fprintf(fp,"%i\n", boundryConditions);

}