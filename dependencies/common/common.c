#include "common.h"
#include <stdlib.h>

int clearScreen()
{
    #if defined(__linux__)
    system("clear");
    #else
    system("cls");
    #endif
}