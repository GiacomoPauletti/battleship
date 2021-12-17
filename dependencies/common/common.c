#include "common.h"
#include <stdlib.h>
#include <string.h>
#if !defined(__linux__)
#include <conio.h>
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

/* Prints the given string centered in the terminal screen.
 * Adds '\n' at the end */
int printCenter(char string[])
{
    int length = strlen(string);
    int padlen = (length >= WIN_SIZE) ? 0 : ( WIN_SIZE - length ) / 2;
    printf("%*s%s%*s\n", padlen, "", string, padlen, "");

    return 1;
}

/* Prints the given string centered in the terminal screen.
 * It does not add '\n' at the end ('nln' means Not New Line) */
int printnlnCenter(char string[])
{
    int length = strlen(string);
    int padlen = (length >= WIN_SIZE) ? 0 : ( WIN_SIZE - length ) / 2;
    printf("%*s%s%*s", padlen, "", string, padlen, "");

    return 1;
}

/* Function used to remove new line from string */
void filterNewLine(char string[])
{
    int cursorA, cursorB;

    cursorA = cursorB = 0;

    while ( string[cursorA] != '\0' )
    {
        if ( string[cursorA] != '\n')
        {
            string[cursorB] = string[cursorA];
            cursorB++;
        }
        cursorA++;
    }

    string[cursorB] = '\0';

}
