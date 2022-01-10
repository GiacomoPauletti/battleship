#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <errno.h>

#ifndef GENERIC_H

#define GENERIC_H 1


#if defined(__linux__)
    #define NULL_FILE "/dev/null"
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_S "/"
#else
    #define NULL_FILE "nul"
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_S "\\"
#endif

#define MAX_PATH_LENGTH 70
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
    struct folderData *folders;

} FolderData;

/* Checks whether the given dir is valid.
 * Parameters:
 *  - path, the file / dir path to check
 *  - beginsWith (optional, if not needed pass "")
 * Returns:
    - -1 if path is not valid
    - 0 if path is valid but dir/file not existing
    - 1 if path is valid and dir/file existing
*/
int checkPath(char path[MAX_PATH_LENGTH], char beginsWith[MAX_PATH_LENGTH]);


int createFile(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LENGTH]);

static int internal_createFile(FileData fileData);


#endif