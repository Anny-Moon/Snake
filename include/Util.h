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