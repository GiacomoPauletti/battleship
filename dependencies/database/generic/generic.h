#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <errno.h>

#if defined(__linux__)
    #include <sys/stat.h>
    #define mkdir(path, mask) mkdir(path, mask)
#else 
    #include <direct.h>
    #define mkdir(path, mask) _mkdir(path)
#endif

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

#define MAX_FILE_NAME_LEN 20
#define MAX_PATH_LEN ( MAX_FILE_NAME_LEN * 6 + 5)

#define MAX_COMMAND_LEN ( 15 + MAX_PATH_LEN )

#define MAX_FILES 10
#define MAX_FOLDERS 10

typedef struct fileData
{
    char name[MAX_FILE_NAME_LEN];
    char path[MAX_PATH_LEN];
    /* absolute path
     * contains file name */

    struct fileData *next;

    int isInit;

} FileData;


typedef struct folderData
{
    char name[MAX_FILE_NAME_LEN];
    char path[MAX_PATH_LEN];

    /* files inside this folder */
    int numFiles;
    FileData *files;

    /* folders inside this folder */
    int numFolders;
    struct folderData *folders; //this is a linked list

    /* next folder in the linked list */
    struct folderData *next;

    int isInit;

} FolderData;


/* Checks whether the given dir is valid.
 * Parameters:
 *  - path, the file / dir path to check
 *  - beginsWith (optional, if not needed pass ""), parent folder from which path have to start
 * Returns:
    - -1 if path is not valid
    - 0 if path is valid but dir/file not existing
    - 1 if path is valid and dir/file existing
*/
int checkPath(char path[MAX_PATH_LEN], char beginsWith[MAX_PATH_LEN]);

/* Allocate space in memory for folderData 
 * 
 * NOTE:
 * variables of type FolderData cannot be properly
 * used without initialization*/
FolderData *initFolder(FolderData *folderData);

/* Checks whether folder has been initialized (correctly) */
int isInitFolder(FolderData *folderData);

/* Deletes folderdata from memory (heap) */
int deallocFolder(FolderData *folderData);

/* Allocate space in memory for fileData
 * 
 * NOTE:
 * variables of type FileData cannot be properly
 * used without initialization*/
FileData *initFile(FileData *fileData);

/* Checks whether file has been initialized (correctly) */
int isInitFile(FileData *fileData)

/* Deletes fileData from memory (heap) */
int deallocFile(FileData *fileData);


/* String Create File ( parameters: file name, parent path )
 * Used to create file with name "name" and parent folder at "parentPath"
 * Name and path are strings */
int screateFile(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LEN]);

/* Create File ( parameter: file data)
 * Used to create file from file data */
int createFile(FileData *newFile);

/* String Create Folder ( parameters: folder name, parent path )
 * Used to create folder with name "name" and parent folder at "parentPath"
 * Name and path are strings */
int screateFolder(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LEN]);

/* Create Folder ( parameter: folder data)
 * Used to create folder from file data */
int createFolder(FolderData *newFolder);

/* Creates and adds a file to a folder (both in the FolderData and in the physical space in disk) */
int addFile(FileData *file, FolderData *folder);

/* Creates and adds a folder to another folder (both in the FolderData and in the physical space in disk) 
 * NOTE: added folder must be empty
 */
int addFolder(FolderData *toAddFolder, FolderData *parentFolder);

/* Move folder inside another one and updates all hierarchy 
 * (subfolders' and subfiles' paths) */
int moveFolder(FolderData *toMoveFolder, FolderData *parentFolder);


#endif