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
* @file Box.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_BOX
#define SNAKE_BOX

#include <ncurses.h>

class Box
{
private:
    
public:
    /** The size of game space */
    int height;
    int width;
    int xStart;//< top left corner
    int yStart;//< top left corner
    
    int top; //< x top border
    int bottom; //< x bottom border
    int left; //< y lefth border
    int right; // y rigth border
    
    int boundryConditions; //< 0 - normal, 1 - pereodic;
    
    Box(int width_in, int height_in, int xStart_in, int yStart_in, int boundryConditions_in = 0);
    ~Box();
    
    void draw() const;
    void writeInFile(FILE* fp) const;
    
};

#endif