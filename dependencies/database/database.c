#include "database.h"

static int createSettings(Database *database, int force);
static int createUserdata(Database *database, int force);
static Setting *setDefaultSettings();
static UData *setDefaultUData();


/* Used only to create database the first time.
 * If database is already present, set "force" to 1 to overwrite it */
Database *createDatabase(int force)
{
    int result;
    char command[ 20 + MAX_PATH_LEN];
    DIR* testDir;
    FolderData *curFolder;
    Database *database;

    
    /* checking if database is present and force is set to 0 */
    testDir = opendir(DATABASE_PATH);
    if ( !testDir && !force ) return NULL;

    /* database is not existing, creating a new one... */
    
    database = malloc(sizeof(Database));
    database -> folder = screateFolder(DATABASE_NAME, "."); 
    //NOTE: screateFolder requires parent folder path, not database path

    if ( database -> folder == NULL )
    {
        #ifdef DEBUG 
        printf("Unable to createFolder %s of database", DATABASE_NAME);
        #endif
        return NULL;
    }

    if ( createUserdata(database, force) != 1 )
    {
        #ifdef DEBUG 
        printf("Unable to createFolder %s of database", USERDATA_NAME);
        #endif

        return NULL;
    }


    if ( createSettings(database, force) != 1 )
    {
        #ifdef DEBUG 
        printf("Unable to createFolder %s of database", USERDATA_NAME);
        #endif

        return NULL;
    }

    return database;
}


/* INTERNAL USE, SHOULD NOT BE USED OUT OF database.c
 * Used only when database is generated to create the "settings" subdirectory.
 * If database is already present, nothing changes.
 * 
 * Upcoming feature: set "force" to 1 to overwrite it */
static int createSettings(Database *database, int force)
{
    FolderData *settings_folder;
    FolderData **curFolder;
    FileData *curFile;

    Setting *settings;

    settings_folder = initFolder(settings_folder);

    //NOTE: screateFolder requires parent folder path, not settings path
    settings_folder = screateFolder(SETTINGS_NAME, DATABASE_PATH);
    if ( settings_folder == NULL ) return 0;

    curFile = screateFile(GSETTINGS_NAME, SETTINGS_PATH);
    if ( curFile == NULL ) return 0;
    settings_folder -> numFiles = 1;
    settings_folder -> files = curFile;


    settings = setDefaultSettings();
    database -> settings = settings;

    /*FIXME: it should be used addFile, which avoid knowing how FolderData is 
     * implemented */
    database -> folder -> numFolders++;
    curFolder = &(database -> folder -> folders);
    while ( *curFolder != NULL ) curFolder = &((*curFolder) -> next);
    *curFolder = settings_folder;

    return 1;
}

/* INTERNAL USE, SHOULD NOT BE USED OUT OF database.c
 * store in database default values for settings */
static Setting *setDefaultSettings()
{
    Setting *settings;

    settings = initSetting();

    return settings;
}

/* INTERNAL USE, SHOULD NOT BE USED OUT OF database.c
 * Used only when database is generated to create the "userdata" subdirectory.
 * If database is already present, nothing changes.
 * 
 * Upcoming feature: set "force" to 1 to overwrite it */
static int createUserdata(Database *database, int force)
{
    FolderData *udata_folder;
    FolderData **curFolder;
    FileData *curFile;

    UData *udata;

    //NOTE: screateFolder requires parent folder path, not settings path
    udata_folder = screateFolder(UDATA_NAME, DATABASE_PATH);
    if ( udata_folder == NULL ) return 0;

    curFile = screateFile(F_UDATA_NAME, UDATA_PATH);
    if ( curFile == NULL ) return 0;
    udata_folder -> numFiles = 1;
    udata_folder -> files = curFile;

    udata = setDefaultUData();

    database -> userdata = udata;

    /*FIXME: it should be used addFile, which avoid knowing how FolderData is 
     * implemented */
    database -> folder -> numFolders++;
    curFolder = &(database -> folder -> folders);
    while ( *curFolder != NULL ) curFolder = &((*curFolder) -> next);
    *curFolder = udata_folder;

    return 1;
}
    
/* INTERNAL USE, SHOULD NOT BE USED OUT OF database.c 
 * store in database default values for userdata */
static UData *setDefaultUData()
{

    UData *udata;

    udata = initUData();

    return udata;
}

/* Allocate space in memory for setting and set default
 * values for some fields.
 *
 * NOTE:
 * variables of type Setting cannot be used properly 
 * without initialization */
Setting *initSetting()
{
    Setting *setting;
    setting = malloc(sizeof(Setting));

    setting -> isInit = 1;
    setting -> next = NULL;
    
    return setting;
}

/* Deletes setting from memory */
int deallocSetting(Setting *setting)
{
    free(setting);
    return 1;
}

/* Allocate space in memory for udata and set default
 * values for some fields.
 *
 * NOTE:
 * variables of type UData cannot be used properly 
 * without initialization */
UData *initUData()
{
    UData *udata;
    udata = malloc(sizeof(UData));

    udata -> isInit = 1;
    udata -> next = NULL;
    
    return udata;
}

/* Deletes udata from memory */
int deallocUData(UData *udata)
{
    free(udata);
    return 1;
}

/* used to debug:
 *      - createDatabase, createSettings/Userdata, setDefaultSetting/UData
 *        initSetting/UData, deallocSetting/UData 
int main()
{
    Database *database;
    database = createDatabase(1);

    return 0;
}
 */