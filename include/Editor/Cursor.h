/* Copyright 2018 Anna Sinelnikova
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
* @file Cursor.h
* @autor Anna Sinelnikova
* @data 2018
*/


#include "../Box.h"
#pragma once

class Cursor{
private:
    char symbol;
    int color;
    
public:
    int x;
    int y;
    
    enum class Mode{standBy, draw, erase} mode;
    
    Cursor(int xStart, int yStart);
    ~Cursor();
    
    void draw() const;
    void erase() const;
    void newCoordinates(int arrowKey, const Box& box);
    void changeMode(Mode newMode);
    
    inline void setX(int value);
    inline void setY(int value);

};

inline void Cursor::setX(int value){
    x = value;
}

inline void Cursor::setY(int value){
    y = value;
}