#include <stdio.h>
#include "menu.h"

#if !defined(__linux__)
#include <conio.h>
#endif


typedef struct {} GameSettings;

typedef int (* GameHandler)(Player *player1, Player *player2);

void turnHandler(Player *player1, Player *player2, GameHandler gameHandler1, GameHandler gameHandler2);

void localMatchMenu(MenuData data);

void LANMatchMenu(MenuData data);

void playLocal(MenuData);

int winHandler(Player *player1, Player *player2);

void filterNewLine(char string[]);

void mainMenu(MenuData data)
{
    char input;
    int isExit;


    isExit = 0;
    input = '\0';
    while ( isExit == 0 )
    {
        if ( input != '\n' )
        {
            clearScreen();
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
            printf("\n\n");
            printCenter("|--------------------------------------------- MAIN MENU ---------------------------------------------|");
            printf("\n");
            printCenter("Select between the following options and press enter:");
            printCenter("0] Local match");
            printCenter("1] LAN match");
            printCenter("2] General settings");
            printCenter("3] Info and scoreboards");
            printCenter("4] Exit");
        }
            

        input = getch_();
        switch (input)
        {
            case '0': 
                localMatchMenu((MenuData) {});
                break;
            case '1': 
                LANMatchMenu((MenuData) {});
                break;
            case '2': 
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '3': 
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '4':
                isExit = 1;
                break;
            
        }
    }

    clearScreen();

}

/*
GameSettings loadGameSettings()
{
    GameSettings settings;
    return settings;
}
*/

void localMatchMenu(MenuData data)
{
    char input;
    int backToMenu;

    backToMenu = 0;
    input = '\0';
    while ( backToMenu == 0 )
    {

        if ( input != '\n' )
        {
            clearScreen();
            printCenter("|------------------------------------------ LOCAL MATCH MENU -----------------------------------------|");
            printf("\n\n");
            printCenter("Select between the following options and press enter:");
            printCenter("0] Play");
            printCenter("1] Game settings");
            printCenter("2] Info");
            printCenter("3] Back to menu");
        }

        input = getch_();
        switch (input)
        {
            case '0':
                playLocal( (MenuData) {});
                backToMenu = 1;
                break;
            case '1':
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '2':
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '3':
                backToMenu = 1;
                break;
            default:
                break;
        }
    }
}

void LANMatchMenu(MenuData data)
{
    char input;
    int backToMenu;

    backToMenu = 0;
    input = '\0';
    while ( backToMenu == 0 )
    {

        if ( input != '\n') 
        {
            clearScreen();
            //printCenter("|—————————————————————————————————————————— LAN MATCH MENU —————————————————————————————————————————|");
            printCenter("|------------------------------------------ LAN MATCH MENU ------------------------------------------|");
            printf("\n\n");
            printCenter("Select between the following options and press enter:");
            printCenter("0] Create match");
            printCenter("1] Join match");
            printCenter("2] Game settings");
            printCenter("3] Info");
            printCenter("4] Back to menu");
        }

        input = getch_();
        switch (input)
        {
            case '0':
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '1':
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '2':
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '3':
                clearScreen();
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                break;
            case '4':
                backToMenu = 1;
                break;
            default:
                break;
        }
    }
}

void playLocal(MenuData data)
{
    Player player1, player2;

    Army defaultArmy;
    GameSettings curSettings;

    /* ------------------------------ PLAYERS' NAMES INPUT ---------------------------- */
    clearScreen();
    do
    {
        printf("Player1, please select your name \n ->");
        fgets(player1.name, MAX_NAME_LENGTH, stdin);
        printf("\n");

        if (player1.name[0] == '\n' && player1.name[0] != '\0')
        {
            clearScreen();
        }
    }while(player1.name[0] == '\n' && player1.name[0] != '\0');

    filterNewLine(player1.name);

    do
    {
        printf("Player2, please select your name \n ->");
        fgets(player2.name, MAX_NAME_LENGTH, stdin);

        if (player2.name[0] == '\n' && player2.name[0] != '\0')
        {
            clearScreen();
        }
    }while(player2.name[0] == '\n' && player2.name[0] != '\0');

    filterNewLine(player2.name);

    //curSettings = loadGameSettings();

    /* ----------------------------------- GAME SETUP --------------------------------- */

    clearScreen();
    printf("Great, now let's setup the game...\n\n");

    /* setting map dimensions */
    player2.attackMap.dims.x = player2.defenceMap.dims.x = player1.attackMap.dims.x = player1.defenceMap.dims.x = MAP_WIDTH;
    player2.attackMap.dims.y = player2.defenceMap.dims.y = player1.attackMap.dims.y = player1.defenceMap.dims.y = MAP_WIDTH;

    empty(&(player1.attackMap));
    empty(&(player1.defenceMap));

    //printf("Here it is: %c\n", player1.defenceMap.map[0][0]);

    empty(&(player2.attackMap));
    empty(&(player2.defenceMap));

    player1.winner = player2.winner = 0;

    player1.shipNumber = player2.shipNumber = DEFAULT_SHIP_NUM;


    initDefaultArmy(&defaultArmy);
    

    printf("%s, it's time to place your ships!\n", player1.name);
    printf("When your are ready, press enter... ");
    fflush(stdin);
    (void) getch_();

    playerArmySetup(&player1, defaultArmy);

    printf("%s, it's time to place your ships!\n", player2.name);
    printf("When your are ready, press enter... ");
    fflush(stdin);
    (void) getch_();

    playerArmySetup(&player2, defaultArmy);

    #if defined(DEBUG_MENU) || defined(DEBUG_ALL)
    // DEBUGGING
    FILE* pfile;

    //pfile = fopen("data/player_army.txt", "w+");
    //fwrite(&(player1), sizeof(player1), 1, pfile);
    //fwrite(&(player2), sizeof(player1), 1, pfile);

    pfile = fopen("player_army.txt", "r");
    fread(&(player1), sizeof(player1), 1, pfile);
    fread(&(player2), sizeof(player2), 1, pfile);

    printMap(player1.defenceMap);
    printMap(player2.defenceMap);
  
    fclose(pfile);

    // end of DEBUGGING
    #endif

    printf("|--------------------------------------------- BATTLESHIP MATCH ---------------------------------------------| \n");
    turnHandler(&player1, &player2, localGameHandler, localGameHandler);

    if ( player1.winner == 1 ) winHandler(&player1, &player2);
    else if (player2.winner == 1 ) winHandler(&player2, &player1);
    else printf("Something went wrong.\nNobody won :(\n");

    printf("\n\n");
    printCenter("Press 'k' and enter to go back to menu");
    while (getch_() != 'k');

}

void turnHandler(Player *player1, Player *player2, GameHandler gameHandler1, GameHandler gameHandler2)
{
    int numSunkP1, numSunkP2;
    int result;
    Player *curPlayer;

    numSunkP2 = numSunkP1 = 0;

    curPlayer = player1; 
    while ( numSunkP1 < player1 -> shipNumber && numSunkP2 < player2 -> shipNumber )
    {
        printf("%s, it's your turn: \n", curPlayer -> name);
        printf("Ship sunk till now %d\n", numSunkP1);
         
        if ( curPlayer == player1 )
        {
            result = gameHandler1(player1, player2);

            if ( result == 1 )
            /* one ship has been sunk */
            {
                numSunkP2++;
            }

            curPlayer = player2;
        }
        else
        {
            result = gameHandler2(player2, player1);

            if ( result == 1 )
            /* one ship has been sunk */
            {
                numSunkP1++;
            }

            curPlayer = player1;
        }

    }
    
    if ( numSunkP1 > numSunkP2 ) player2 -> winner = 1;
    else player1 -> winner = 1;

}

int winHandler(Player *player1, Player *player2)
{
    char string[100 + MAX_NAME_LENGTH];

    clearScreen();
    sprintf(string, "Congratulation %s you won this match!!\n", player1 -> name);
    printCenter(string);

    return 1;
}
