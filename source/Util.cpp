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
* @file Util.cpp
* @autor Anna Sinelnikova
* @data 2018
*/


#include "../include/Util.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> // required for stat.h
#include <sys/stat.h>
#include <string>

std::string user = getenv("HOME"); //path to ~/
std::string PATH_TO_DIR_STR = user + "/.snake";
const char* PATH_TO_DIR = PATH_TO_DIR_STR.c_str();

bool Util::isFirstRun=false;
//std::vector<char[]> Util::levelDefault;

std::vector<std::string> Util::levelDefault{\
"level 1\n\
25	15	5	5 #box\n\
1	#periodic boundry conditios\n\
OBSTACLES\n\
END",\
\
"level 2\n\
35	20	5	5 #box\n\
1	#periodic boundry conditios\n\
OBSTACLES\n\
6	3	10	7\n\
6	3	29	7\n\
6	3	10	20\n\
6	3	29	20\n\
END",\
\
"level 2\n\
41	21	5	5 #box\n\
1	#periodic boundry conditios\n\
OBSTACLES\n\
1	21	25	5\n\
41	1	5	15\n\
END"\
};

void Util::createDir(const std::string fullName){
    bool isDirExists=false;
    int nError = 0;
    mode_t nMode = 0733; // UNIX style permissions
    
    struct stat st;
    if(stat(PATH_TO_DIR,&st) == 0){
	if((st.st_mode & S_IFDIR) != 0){
//	    printf("exist\n");
	    isDirExists = true;
	    Util::isFirstRun = false;
	}
    }
    else{
//	printf("NOT exist\n");
	isDirExists = false;
	Util::isFirstRun = true;
    }
    
    if(!isDirExists){
	printf("I created the directory: '%s'.\n", PATH_TO_DIR);
	printf("It will be used for the game files.\n");
	nError = mkdir(PATH_TO_DIR, nMode);
    }
    
    if (nError != 0) {
	printf("Error:\n\tcannot create dir '%s'.\n",PATH_TO_DIR);
	exit(1);
    }

}

void Util::createDefaultLevelFile(int levelNum){
    FILE* fp;
    char* levelName;
    levelName = new char[1000];
    sprintf(levelName,"%s/_level%i.dat", PATH_TO_DIR, levelNum+1);
    fp = fopen(levelName, "w");
    fprintf(fp,"%s",Util::levelDefault[levelNum].c_str());
    fclose(fp);
    delete [] levelName;
}