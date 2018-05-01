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
* @file Util.h
* @autor Anna Sinelnikova
* @data 2018
*/


#include <string>
#include <vector>

#ifndef ANNA_UTIL
#define ANNA_UTIL

extern std::string PATH_TO_DIR_STR;
extern const char* PATH_TO_DIR;

class Util{
public:
    /** If the program run for the first time*/
    static bool isFirstRun;
    static void createDir(const std::string fullName);
    /** At first launch creates file in defauld dir with level 1*/
    static void createDefaultLevelFile(int levelNum);
    
    static char levelOne[];
    static char levelTwo[];
    static char levelThree[];
    
    static std::vector<std::string> levelDefault;
    
};

#endif