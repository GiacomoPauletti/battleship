#include "database.h"

static int createSettings();
static int setDefaultSettings();


/* Used only to create database the first time.
 * If used again, it does nothing because "data" folder is already present */
int createDatabase()
{
    int result;
    char command[ 20 + MAX_PATH_LENGTH];

    sprintf(command, "ls | grep %s > %s", DATA_PATH, NULL_FILE);
    result = system(command);

    if ( result == 0 ) return -1;
    /* if database is already present, database will not be created */

    sprintf(command, "mkdir %s", DATA_PATH);
    system(command);

    result = createSettings();

    if ( result != 0 ) return -1;

    return 0;
}


/* INTERNAL USE, SHOULD NOT BE USED OUT OF database.c
 * Used only when database is generated to create the "settings" subdirectory.
 * If used again, it does nothing because "settings" folder is already present */
static int createSettings()
{
    int result;
    char settingsPath[MAX_PATH_LENGTH];
    char command[ 20 + MAX_PATH_LENGTH];


    sprintf(settingsPath, "%s/%s", DATA_PATH, SETTINGS_PATH);

    sprintf(command, "mkdir %s", settingsPath);
    result = system(command);
    if ( result != 0 ) return -1;

    sprintf(command, "touch %s/default.txt", settingsPath);
    result = system(command);
    if ( result != 0 ) return -1;

    result = setDefaultSettings();
    if ( result != 0 ) return -1;

    return 0;
}

/* INTERNAL USE, SHOULD NOT BE USED OUT OF database.c
 * Used only when database is generated to fill "settings/default.txt" with default settings */
static int setDefaultSettings()
{
    return 0;
}