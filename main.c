#include <stdio.h>
#include <stdlib.h>
#include "dependencies/map/map.h"
#include "dependencies/ship/ship.h"
#include "dependencies/common/common.h"
#include "dependencies/menu/menu.h"
#include "dependencies/database/database.h"

#define MAX_NAME_LENGTH 20
/* maximum length of player name */

int main()
{
    Player player1, player2;
    int result;

    clearScreen();

    (void) createDatabase();
    /* creating database, if not done yet */

    mainMenu( (MenuData) {});

    return 0;
}
