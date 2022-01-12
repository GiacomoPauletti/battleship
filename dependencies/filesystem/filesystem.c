#include "filesystem.h"

/* INTERNAL USE
 * update paths of parentFolder's subfolders and parentFolder's subfiles.
 * Necessary if moving one folder inside another one */
static int updateHierarchy(FolderData *parentFolder);

int checkPath(char path[MAX_PATH_LEN], char beginsWith[MAX_PATH_LEN])
{
    char beginningPath[MAX_PATH_LEN];
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

/* Allocate space in memory for folderData 
 * 
 * NOTE:
 * variables of type FolderData cannot be properly
 * used without initialization*/
FolderData *initFolder(FolderData *folderData)
{
    folderData = malloc(sizeof(FolderData));
    folderData -> numFolders = 0;
    folderData -> folders = NULL;
    folderData -> numFiles = 0;
    folderData -> files = NULL;

    folderData -> isInit = 1;

    return folderData;
}

/* Checks whether folder has been initialized (correctly) */
int isInitFolder(FolderData *folderData)
{
    return (folderData -> isInit != 1) ? 0 : 1;
}

/* Deletes folderdata from memory (heap) */
int deallocFolder(FolderData *folderData)
{
    FolderData *curFolder, *tmpFolder;
    FileData *curFile, *tmpFile;

    curFolder = folderData -> folders;

    while ( curFolder != NULL )
    {
        tmpFolder = curFolder;
        curFolder = curFolder -> next;
        fflush(stdout);
        deallocFolder(tmpFolder);        
    }

    curFile = folderData -> files;
    while ( curFile != NULL )
    {
        fflush(stdout);
        tmpFile = curFile;
        curFile = curFile -> next;
        deallocFile(tmpFile);        
    }

    fflush(stdout);
    free(folderData);
    return 1;
}

/* Allocate space in memory for fileData
 * 
 * NOTE:
 * variables of type FileData cannot be properly
 * used without initialization*/
FileData *initFile(FileData *fileData)
{
    fileData = malloc(sizeof(FileData));
    fileData -> next = NULL;

    fileData -> isInit = 1;

    return fileData;
}

/* Checks whether file has been initialized (correctly) */
int isInitFile(FileData *fileData)
{
    return (fileData -> isInit != 1) ? 0 : 1;
}

/* Deletes fileData from memory (heap) */
int deallocFile(FileData *fileData)
{
    free(fileData);
    return 1;
}

/* Returns 1 if folder do not contain files or folders (otherwise returns 0) */
int isEmptyFolder(FolderData *folder)
{
    return ( ( folder -> files == NULL ) && ( folder -> folders == NULL ) ) ? 1 : 0;
}

/* Creates a file from 2 strings:
 *   - name: file name
 *   - parentPath: path of containing folder
 * 
 * Returns the data relative to the file (FileData variable) if file was successfully
 * created, otherwise returns NULL
 */
FileData * screateFile(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LEN])
{
    int result;
    FileData *newFile;

    if (name[0] == PATH_SEPARATOR) return NULL;
    
    newFile = initFile(newFile);

    if ( strcpy(newFile -> name, name) == NULL ) return NULL;
    if ( strcpy(newFile -> path, parentPath) == NULL ) return NULL;
    if ( newFile -> path[strlen(newFile -> path) - 1] != PATH_SEPARATOR)
        if ( strcat(newFile -> path, PATH_SEPARATOR_S) == NULL ) return NULL;
    if ( strcat(newFile -> path, name) == NULL ) return NULL;

    if ( createFile(newFile) == 1 ) return newFile;
    else return NULL;
}


/* Creates a file from FileData variable */
int createFile(FileData *newFile)
{
    int cursor;
    FILE *createdFile;

    createdFile = fopen(newFile -> path, "w");
    if ( createdFile == NULL ) return 0;
    return 1;
}

/* Creates a folder from 2 strings:
 *   - name: folder name
 *   - parentPath: path of containing folder
 * 
 * Returns the data relative to the folder (FolderData variable) if folder was successfully
 * created, otherwise returns NULL
*/
FolderData *screateFolder(char name[MAX_FILE_NAME_LEN], char parentPath[MAX_PATH_LEN])
{
    FolderData *newFolder;
    int result;

    newFolder = initFolder(newFolder);

    if ( name[0] == PATH_SEPARATOR ) return NULL;
    if ( strcpy(newFolder -> name, name) == NULL ) return NULL;
    if ( strcpy(newFolder -> path, parentPath) == NULL ) return NULL;
    if ( newFolder -> path[strlen(newFolder -> path) - 1] != PATH_SEPARATOR)
        if ( strcat(newFolder -> path, PATH_SEPARATOR_S) == NULL ) return NULL;
    if ( strcat(newFolder -> path, name) == NULL ) return NULL;

    if ( createFolder(newFolder) == 1 ) return newFolder;
    else return NULL;
}


/* Creates a folder from FolderData variable */
int createFolder(FolderData *newFolder)
{
    int result;
    FILE *newFile;
    FileData *curFile;
    FolderData *curFolder;
    int newSubFolder;

    /* creating the folder */
    errno = 0;
    result = mkdir(newFolder -> path, S_IRWXU);

    if ( errno != 0 ) return 0;

    /* creating files inside folder */
    curFile = newFolder -> files;
    while ( curFile != NULL )
    {
        sprintf(curFile -> path, "%s%c%s", newFolder -> path, PATH_SEPARATOR, curFile -> name);

        errno = 0;
        newFile = fopen(curFile -> path, "w");
        if ( newFile != NULL ) fclose(newFile);

        curFile = curFile -> next;

        if ( errno != 0 ) fclose(newFile);

        #if defined(DEBUG)
        if ( errno != 0 ) printf("[createFolder] ERROR! Error in creation of subfile %s\n", 
        newFolder -> files[counter].path);
        #endif
    }

    /* creating files inside folder */
    curFolder = newFolder -> folders;
    while ( curFolder != NULL )
    {
        sprintf(curFolder -> path, "%s%c%s", newFolder -> path, PATH_SEPARATOR, curFolder -> name);

        errno = 0;
        newSubFolder = mkdir(curFolder -> path, S_IRWXU);

        #if defined(DEBUG)
        if ( errno != 0 ) printf("[createFolder] ERROR! Error in creation of subfolder %s\n", 
        newFolder -> folders[counter].path);
        #endif
    }

    return 1;
}

/* Creates and adds a file to a folder (both in the FolderData and in the physical space in disk) */
int addFile(FileData *file, FolderData *folder)
{
    FILE *newFile;
    FileData **curFile;
    char filePath[MAX_PATH_LEN];

    if ( isInitFolder(folder) != 1 )
    {
        printf("Unable to add file '%s' to folder '%s'. Folder not initialized \n", 
                file -> name, folder -> name);
        return 0;
    }

    if ( isInitFile(file) != 1 ) 
    {
        printf("Unable to add file '%s' to folder '%s'. File not initialized \n", 
                file -> name, folder -> name);
        return 0;
    }

    if ( folder -> numFiles >= MAX_FILES )
    {
        printf("Unable to add file '%s' to folder \"%s\".\nMax number of subfiles reached\n", 
                file -> name, folder -> name);
        return 0;
    }

    // updating path of file
    sprintf(file -> path, "%s%c%s", folder -> path, PATH_SEPARATOR, file -> name);
    

    // creating toAddFolder
    newFile = fopen(file -> path, "w");
    if ( newFile == NULL ) return 0;

    // updating files list of folder
    curFile = &(folder -> files);
    while ( *curFile != NULL ) curFile = &((*curFile) -> next);

    *curFile = file;
    folder -> numFiles++;
    file -> next = NULL;

    if ( fclose(newFile) == EOF ) return 0;
    return 1;
}

/* Creates and adds a folder to another folder (both in the FolderData and in the physical space in disk) 
 * NOTE: added folder must be empty
 */
int addFolder(FolderData *toAddFolder, FolderData *parentFolder)
{
    int newFolder;
    FolderData **curFolder;

    if ( isInitFolder(parentFolder) != 1 )
    {
        printf("Unable to add folder '%s' to folder '%s'. ParentFolder '%s' not initialized \n", 
                toAddFolder -> name, parentFolder -> name, parentFolder -> name );
        return 0;
    }

    if ( isInitFolder(toAddFolder) != 1 ) 
    {
        printf("Unable to add folder '%s' to folder '%s'. SubFolder not initialized \n", 
                toAddFolder -> name, parentFolder -> name);
        return 0;
    }

    if ( parentFolder -> numFolders >= MAX_FILES )
    {
        printf("Unable to add folder '%s' to folder \"%s\".\nMax number of subfolders reached\n", 
                toAddFolder -> name, parentFolder -> name);
        return 0;
    }

    if ( isEmptyFolder(toAddFolder) != 1 )
    {
        printf("Unable to add folder '%s' to folder '%s'. Folder '%s' is non-empty\n", 
        toAddFolder -> name, parentFolder -> name, toAddFolder -> name);
    }

    // updating path of toAddFolder
    sprintf(toAddFolder -> path, "%s%c%s", parentFolder -> path, PATH_SEPARATOR, toAddFolder -> name);
    
    // creating toAddFolder
    createFolder(toAddFolder);

    // updating subfolder list of folder
    curFolder = &(parentFolder -> folders);
    while ( *curFolder != NULL ) curFolder = &((*curFolder) -> next);
    *curFolder = toAddFolder;

    toAddFolder -> next = NULL;
    parentFolder -> numFolders++;

    updateHierarchy(toAddFolder);

    errno = 0;        
    if ( errno != 0 ) return 0;
    
    return 1;
}

/* Move folder inside another one and updates all hierarchy 
 * (subfolders' and subfiles' paths) */
int moveFolder(FolderData *toMoveFolder, FolderData *parentFolder)
{
    char mvCommand[20 + (MAX_PATH_LEN * 2)];
    FolderData **curFolder;

    /* checking if movement is possible */
    if ( isInitFolder(parentFolder) != 1 ) 
    {
        printf("Unable to move folder '%s' to folder '%s'. Folder '%s' not initialized \n", 
                toMoveFolder -> name, parentFolder -> name, parentFolder -> name );
        return 0;
    }

    if ( isInitFolder(toMoveFolder) != 1 ) 
    {
        printf("Unable to add folder '%s' to folder '%s'. SubFolder not initialized \n", 
                toMoveFolder -> name, parentFolder -> name);
        return 0;
    }

    if ( parentFolder -> numFolders >= MAX_FILES )
    {
        printf("Unable to add folder '%s' to folder \"%s\".\nMax number of subfolders reached\n", 
                toMoveFolder -> name, parentFolder -> name);
        return 0;
    }

    /* moving the first folder inside the second one */
    #if defined(__linux__)
    sprintf(mvCommand, "mv %s %s", toMoveFolder -> path, parentFolder -> path);
    #else
    sprintf(mvCommand, "move %s %s", toMoveFolder -> path, parentFolder -> path);
    #endif

    sprintf(toMoveFolder -> path, "%s%c%s", 
            parentFolder -> path, PATH_SEPARATOR, toMoveFolder -> name);

    system(mvCommand);

    curFolder = &(parentFolder -> folders);
    while ( *curFolder != NULL ) *curFolder++;
    *curFolder = toMoveFolder;

    toMoveFolder -> next = NULL;
    parentFolder -> numFolders++;

    /* updating folder inner hierarcy */
    updateHierarchy(toMoveFolder);

    return 1;
}

/* INTERNAL USE
 * update paths of parentFolder's subfolders and parentFolder's subfiles.
 * Necessary if moving one folder inside another one */
static int updateHierarchy(FolderData *parentFolder)
{
    FolderData *curFolder;
    FileData *curFile;
    char tmpPath[MAX_PATH_LEN];

    /* updates hierarchy (paths) for each file */
    curFile = parentFolder -> files;
    while ( curFile != NULL )
    {
        sprintf(curFile -> path, "%s%c%s", parentFolder -> path, PATH_SEPARATOR, curFile -> name);
        curFile = curFile -> next;
    }

    /* updates hierarchy (paths) for each folder and recursively updates folder's 
     * subfolders */
    curFolder = parentFolder -> folders;
    while ( curFolder != NULL )
    {
        sprintf(curFolder -> path, "%s%c%s", parentFolder -> path, PATH_SEPARATOR, curFolder -> name);
        updateHierarchy(curFolder);
    }

    return 1;
}


/*
USED FOR DEBUGGING THE FOLLOWING FUNCTIONS
    -initFolder
    -createFolder
    -moveFolder
    -addFolder
    -addFile
    -deallocFolder
    -deallocFile
int main()
{
    FolderData *parentFolder;
    FolderData *subFolder;
    FileData *subFile;

    printf("Before everything\n");
    fflush(stdout);
    parentFolder = initFolder(parentFolder);

    subFolder = initFolder(subFolder);
    printf("Both folders init'ed\n");
    fflush(stdout);
    
    strncpy(subFolder -> name, "childFolder", MAX_FILE_NAME_LEN);
    strncpy(subFolder -> path, "./childFolder", MAX_PATH_LEN);
    printf("Added subFolder name and path\n");
    fflush(stdout);

    // uncomment this to test addFile (but you have to remove the "addFolder" part)
    #if 0
    subFolder -> numFiles = 1;
    subFile = initFile(subFile);
    printf("File init'ed\n");
    fflush(stdout);

    strncpy(subFile -> name, "file.txt", MAX_FILE_NAME_LEN);
    printf("Added file name\n");
    fflush(stdout);

    createFolder(subFolder);
    printf("Created subFolder\n");
    fflush(stdout);

    addFile(subFile, subFolder);
    printf("Added file to subFolder\n");
    fflush(stdout);
    #endif

    subFolder -> numFolders = 0;

    strncpy(parentFolder -> name, "parentFolder", MAX_FILE_NAME_LEN);
    strncpy(parentFolder -> path, "./parentFolder", MAX_PATH_LEN);
    printf("Added parentFolder name and path\n");
    fflush(stdout);

    parentFolder -> numFiles = 0;
    parentFolder -> numFolders = 1;


    createFolder(parentFolder);
    printf("Created parent folder\n");
    fflush(stdout);


    addFolder(subFolder, parentFolder);
    printf("Added subFolder to parentFolder\n");
    fflush(stdout);

    // uncomment this to test addFile (but you have to remove the "addFolder" part)
    #if 0
    moveFolder(subFolder, parentFolder);
    printf("Moved subFolder into parent folder\n");
    fflush(stdout);
    #endif

    deallocFolder(parentFolder);

}
*/