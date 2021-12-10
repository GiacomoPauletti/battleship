#include "common.h"
#include <stdlib.h>
#if !defined(__linux__)
#include <cursio.h>
#endif

int clearScreen()
{
    #if defined(__linux__)
    system("clear");
    #else
    system("cls");
    #endif
}

char getch_()
{
    #if defined(__linux__)
    getchar();
    #else
    getch();
    #endif
}