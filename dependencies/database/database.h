#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"

#ifndef SETTINGS_H
#define SETTINGS_H

#define MAX_PATH_LENGTH 50
#define DATA_PATH "data"
/* database path */
#define SETTINGS_PATH "settings"

#define CMD_BUF_PATH "cmd_buf.txt"
/* path to file used to store command results */

#if defined(__linux__)
    #define NULL_FILE "/dev/null"
#else
    #define NULL_FILE "nul"
#endif

int createDatabase();

#endif