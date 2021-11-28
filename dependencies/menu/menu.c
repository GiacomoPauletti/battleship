#include <stdio.h>
#include "menu.h"

#if !defined(__linux__)
#include <cursio.h>
#endif


typedef struct {} GameSettings;

void playLocal(MenuData);

void mainMenu(MenuData data)
{
    printf("|———————————————————————— MAIN MENU ————————————————————————|\n");
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

    

    player1.shipNumber = player2.shipNumber = DEFAULT_SHIP_NUM;


    initDefaultArmy(&defaultArmy);
    

    printf("%s, it's time to place your ships!\n", player1.name);
    printf("When your are ready, press enter... ");
    (void) getchar();

    /* con i numeri da 1 a 10 seleziona la nave da piazzare
     *      -> di fianco fa vedere i numeri delle navi, facendo vedere se è stata messa o meno
     *
     * con wasd sposta il cursore sulla mappa
     * con r ruota la nave
     * con '\n' (enter) inserisce la nave
     * come si puo cancellare una nave già messa?
     *      -> quando con un numero si seleziona una nave già messa poi con - si può rimuovere
     *         la nave già posizionata
     */
    
    playerArmySetup(&player1, defaultArmy);
    //playerArmySetup(&player2, defaultArmy);
        
    
}

