#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../common/common.h"
#include "generic/generic.h"

#ifndef DATABASE_H
#define DATABASE_H

#define DATA_PATH "data"
/* database path */
#define SETTINGS_PATH "settings"

#define CMD_BUF_PATH "cmd_buf.txt"
/* path to file used to store command results */


// to change max files and folder uncomment the following lines:
//#define MAX_FILES 10
//#define MAX_FOLDERS 10

int createDatabase();
/* creates all the database */

#endif