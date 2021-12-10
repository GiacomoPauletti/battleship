#include <stdio.h>
#include "menu.h"

#if !defined(__linux__)
#include <cursio.h>
#endif


typedef struct {} GameSettings;

typedef int (* GameHandler)(Player *player1, Player *player2);

void turnHandler(Player *player1, Player *player2, GameHandler gameHandler1, GameHandler gameHandler2);

void playLocal(MenuData);

int winHandler(Player *player1, Player *player2);

void mainMenu(MenuData data)
{
    printf("|————————————————————————————————————————————— MAIN MENU —————————————————————————————————————————————|\n");
    printf("\n");
    //printf("Choose between the following options:\n");

    playLocal( (MenuData) {} );
}

GameSettings loadGameSettings()
{
    GameSettings settings;
    return settings;
}

void playLocal(MenuData data)
{
    Player player1, player2;

    Army defaultArmy;
    GameSettings curSettings;

    /* ------------------------------ PLAYERS' NAMES INPUT ---------------------------- */
    printf("Player1, please select your name \n ->");
    fgets(player1.name, MAX_NAME_LENGTH, stdin);

    printf("Player2, please select your name \n ->");
    fgets(player2.name, MAX_NAME_LENGTH, stdin);

    curSettings = loadGameSettings();

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

    //playerArmySetup(&player1, defaultArmy);

    printf("%s, it's time to place your ships!\n", player2.name);
    printf("When your are ready, press enter... ");
    fflush(stdin);
    (void) getch_();

    //playerArmySetup(&player2, defaultArmy);

    // DEBUGGING
    FILE* pfile;

    //pfile = fopen("player_army.txt", "w+");
    //fwrite(&(player1), sizeof(player1), 1, pfile);
    //fwrite(&(player2), sizeof(player1), 1, pfile);

    pfile = fopen("player_army.txt", "r");
    fread(&(player1), sizeof(player1), 1, pfile);
    fread(&(player2), sizeof(player2), 1, pfile);

    // end of DEBUGGING

    printMap(player1.defenceMap);
    printMap(player2.defenceMap);
  
    fclose(pfile);

        
    printf("|————————————————————————————————————————————— BATTLESHIP MATCH —————————————————————————————————————————————|\n");
    turnHandler(&player1, &player2, localGameHandler, localGameHandler);

    if ( player1.winner == 1 ) winHandler(&player1, &player2);
    else if (player2.winner == 1 ) winHandler(&player2, &player1);
    else printf("Something went wrong.\nNobody won :(\n");

    printf("Press any key to go back to menu ...");
    fflush(stdin);
    (void) getch_();

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
        printf("%s, it's your turn: ", curPlayer -> name);
         
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
    printf("Congratulation %s you won this match!!\n", player1 -> name);

    return 1;
}