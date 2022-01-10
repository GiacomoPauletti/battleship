#include "generic.h"

static int internal_createFile(FileData fileData);

int checkPath(char path[MAX_PATH_LENGTH], char beginsWith[MAX_PATH_LENGTH])
{
    char beginningPath[MAX_PATH_LENGTH];
    int pathCursor;
    DIR *dir;
    FILE *file;

    if( strlen(beginsWith) > 0 )
    {
        pathCursor = 0;
        while( ( path[pathCursor] != '\0' ) && ( path[pathCursor] != PATH_SEPARATOR) && ( beginsWith[pathCursor] == path[pathCursor] ) )
        {
            pathCursor++;
        }

        if ( path[pathCursor] != PATH_SEPARATOR ) return -1;
    }

    pathCursor = 0;
    dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    } else if ( (file = fopen(path, "r")) != NULL )
    {
        fclose(file);
        return 1;
    }
    else if (ENOENT == errno) return 0;
}


int createFile(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LENGTH])
{
    int result;
    FileData fileData;

    if (name[0] == PATH_SEPARATOR) return 0;
    
    if ( strcpy(fileData.name, name) == NULL ) return 0;
    if ( strcpy(fileData.path, parentPath) == NULL ) return 0;
    if ( fileData.path[strlen(fileData.path) - 1] != PATH_SEPARATOR)
        if ( strcat(fileData.path, PATH_SEPARATOR_S) == NULL ) return 0;
    if ( strcat(fileData.path, name) == NULL ) return 0;

    result = internal_createFile(fileData);
    return result;
}


static int internal_createFile(FileData fileData)
{
    int cursor;
    int result;
    char filePath[MAX_PATH_LENGTH];
    char command[20 + MAX_PATH_LENGTH];
    

    #if defined(__linux__) 
    sprintf(command, "touch %s", fileData.path);
    #else
    sprintf(command, "type nul > %s", fileData.path);
    #endif

    system(command);
}

/*static int createFolder(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LENGTH], 
)*/

/*static int internal_createFolder(FolderData folderData)
{
    int counter;

    for ( counter = 0; counter < folderData.numFiles; counter++)
    {

    }
}*/
