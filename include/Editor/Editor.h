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
* @file Editor.h
* @autor Anna Sinelnikova
* @data 2018
*/

#pragma once
#include "../../include/Editor/Cursor.h"
#include "../../include/Box.h"

#include <ncurses.h>


#define _IS_NUMBER(ch)\
    ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9'
    
class Editor{
    
public:
    void static loop(Cursor* cursor, int ch);
    void static boxRescale(int ch, Box* box);
    void static start(int ch);
};