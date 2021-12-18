#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"

#ifndef SETTINGS_H
#define SETTINGS_H

#define MAX_PATH_LENGTH 70
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

#define MAX_FILE_NAME_LEN 20
#define MAX_FILES 10
#define MAX_FOLDERS 10

typedef struct fileData
{
    char name[MAX_FILE_NAME_LEN];
    char path[MAX_PATH_LENGTH];
    /* absolute path
     * contains file name */

} FileData;

typedef struct folderData
{
    char name[MAX_FILE_NAME_LEN];

    /* files inside this folder */
    int numFiles;
    FileData files[MAX_FILES];

    /* folders inside this folder */
    int numFolders;
    struct folderData folders[MAX_FOLDERS];

} FolderData;


int createDatabase();
/* creates all the database */

#endif