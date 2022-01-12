#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../common/common.h"
#include "../filesystem/filesystem.h"

#ifndef DATABASE_H
#define DATABASE_H

/* database info */
#define DATABASE_NAME "db"
#define DATABASE_PATH "." PATH_SEPARATOR_S DATABASE_NAME
//path is: "./db"

/* game settings info */
#define SETTINGS_NAME "settings"
#define SETTINGS_PATH DATABASE_PATH PATH_SEPARATOR_S SETTINGS_NAME
//path is: "./db/settings"
#define GSETTINGS_NAME "game_settings.txt"
#define GSETTINGS_PATH SETTINGS_PATH PATH_SEPARATOR_S GSETTINGS_NAME
//path is: "./db/settings/game_settings.txt"


/* user data info */
#define UDATA_NAME "userdata"
#define UDATA_PATH DATABASE_PATH PATH_SEPARATOR_S UDATA_NAME
//path is: "./db/userdata"
#define F_UDATA_NAME "userdata.txt"
#define F_UDATA_PATH UDATA_PATH PATH_SEPARATOR_S GUDATA_NAME
//path us : "./db/userdata/userdata.txt"

typedef enum { on, off } StatusValue;

typedef union setting_value
{
    int num;    
    StatusValue status;
} SettingValue;

#define MAX_SETTING_NAME_LEN 20

/* Structure which represent a setting unit (a single setting)*/
typedef struct setting
{
    int id;
    char name[MAX_SETTING_NAME_LEN];
    SettingValue value;

    struct setting *next;

    int isInit;
} Setting;

#define MAX_UDATA_NAME_LEN 20
#define MAX_UDATA_VALUE_LEN 20

/* Structure which represent a userdata unit*/
typedef struct udata
{
    int id;
    char name[MAX_UDATA_NAME_LEN];
    char value[MAX_UDATA_VALUE_LEN];

    struct udata *next;

    int isInit;
} UData;

// to change max files and folder uncomment the following lines:
//#undefine MAX_FILES
//#define MAX_FILES 10
//#undefine MAX_FOLDERS
//#define MAX_FOLDERS 10

typedef struct database
{
    FolderData *folder;
    Setting *settings;
    UData *userdata;
} Database;

Database *createDatabase(int force);
/* creates all the database */

/* FIXME: is it right that the following functions are globally accessible? */
Setting *initSetting();

int deallocSetting(Setting *setting);

UData *initUData();

int deallocUData(UData *udata);

#endif