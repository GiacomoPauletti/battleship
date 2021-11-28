#include <stdio.h>
#include <stdlib.h>
#include "dependencies/map/map.h"
#include "dependencies/ship/ship.h"
#include "dependencies/common/common.h"
#include "dependencies/menu/menu.h"

#define MAX_NAME_LENGTH 20
/* maximum length of player name */

int main()
{
    Player player1, player2;

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif

    printf("\n\n\
oooooooooo.                .       .   oooo                     oooo         o8o                      \n\
`888'   `Y8b             .o8     .o8   `888                     `888         `\"'                      \n\
 888     888  .oooo.   .o888oo .o888oo  888   .ooooo.   .oooo.o  888 .oo.   oooo  oo.ooooo.   .oooo.o \n\
 888oooo888' `P  )88b    888     888    888  d88' `88b d88(  \"8  888P\"Y88b  `888   888' `88b d88(  \"8 \n\
 888    `88b  .oP\"888    888     888    888  888ooo888 `\"Y88b.   888   888   888   888   888 `\"Y88b.  \n\
 888    .88P d8(  888    888 .   888 .  888  888    .o o.  )88b  888   888   888   888   888 o.  )88b \n\
o888bood8P'  `Y888\"\"8o   \"888\"   \"888\" o888o `Y8bod8P' 8\"\"888P' o888o o888o o888o  888bod8P' 8\"\"888P' \n\
                                                                                   888                \n\
                                                                                  o888o               \n\
    ");

    printf("\n\n\n\n");

    mainMenu( (MenuData) {});

    return 0;
}
