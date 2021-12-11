#include <stdio.h>
#include <stdlib.h>
#include "database.h"

static int createSettings();

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

    return 0;
}

