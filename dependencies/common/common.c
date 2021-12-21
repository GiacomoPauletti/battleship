#include "common.h"
#include <stdlib.h>
#include <string.h>
#if !defined(__linux__)
#include <conio.h>
#endif

#define MAX_LINE_LENGTH 300

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

/* Prints centered each substring delimited by '\n' */
int MultiPrintCenter(char string[])
{
    int cursor;
    char currentLine[MAX_LINE_LENGTH];
    int length;

    cursor = 0;
    length = 0;
    while ( string[cursor] != '\0' )
    {
        if ( string[cursor] == '\n' )
        {
            currentLine[length] = '\0';
            printCenter(currentLine);
            length = 0;
        }
        else
        {
            currentLine[length] = string[cursor];
            length++;
        }
        cursor++;
    }

    if ( length > 0 )
    {
        currentLine[length] = '\0';
        printCenter(currentLine);
    }

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
