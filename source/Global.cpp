#include "../include/Global.h"

#include <stdlib.h>
#include <sys/types.h> // required for stat.h
#include <sys/stat.h>
#include <string>

std::string user = getenv("HOME"); //path to ~/
std::string PATH_TO_DIR_STR = user + "/.snake";
const char* PATH_TO_DIR = PATH_TO_DIR_STR.c_str();