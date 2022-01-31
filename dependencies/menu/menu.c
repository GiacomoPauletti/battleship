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

int playHostLAN(MenuData data);

int playGuestLAN(MenuData data);

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
                playHostLAN((MenuData){});

                /*
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back"); 
                while ( getch_() != 'k' );
                */
                break;
            case '1':
                clearScreen();
                playGuestLAN((MenuData){});

                /*
                printf("Not implemented yet!\n");
                printf("Press 'k' and enter to go back");
                while ( getch_() != 'k' );
                */
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
    do
    {
        clearScreen();
        printf("Player1, please select your name \n ->");
        fgets(player1.name, MAX_NAME_LENGTH, stdin);
        printf("\n");

    }while(player1.name[0] == '\n' && player1.name[0] != '\0');

    filterNewLine(player1.name);

    do
    {
        clearScreen();
        printf("Player2, please select your name \n ->");
        fgets(player2.name, MAX_NAME_LENGTH, stdin);
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

int playHostLAN(MenuData data)
{
    Player player1, player2;

    Army defaultArmy;
    GameSettings curSettings;

    DataPacket serverMsg, clientMsg;
    int contentBuf[MAX_PACKETS * CHUNK_SIZE];

    int currID;
    int clientID;
    int numAttempts;
    int result;

    int server_socket, client_socket;
    int addr_len = sizeof(client_socket);
    struct sockaddr_in server_address, client_address;

    errno = 0;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if ( errno != 0 || server_socket == -1 )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_MENU)
        printf("[hostOnlineGame] Unable to create server socket\n", SERVER_PORT);
        #endif

        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if ( errno != 0 )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_MENU)
        printf("[hostOnlineGame] Unable to bind server to port %d\n", SERVER_PORT);
        #endif

        close(server_socket);
        return -1;
    }

    listen(server_socket, MAX_CLIENTS);
    if ( errno != 0 )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_MENU)
        printf("[hostOnlineGame] Unable to start listening for clients\n");
        #endif

        close(server_socket);
        return -1;
    }

    currID = 1;
    clientID = 1;

    printCenter("Waiting for player to join...\n");
    result = paccept(server_socket, client_socket, (struct sockaddr *) &client_address);
    printCenter("Player joined\n");

    /* ------------------------------ PLAYERS' NAMES INPUT ---------------------------- */
    /* Getting host username */
    do
    {
        clearScreen(); 

        printf("Please input your name \n -> ");
        fgets(player1.name, MAX_NAME_LENGTH, stdin);
        printf("\n");

    } while(player1.name[0] == '\n' && player1.name[0] != '\0');

    filterNewLine(player1.name);

    clearScreen();
    printf("Waiting for opponent to choose its name...\n");

    /* Getting client username */
    do
    {
        fillPacket(&serverMsg, ACTION, currID, -1, 1, -1, "input username");

        // asking for username
        sendPacket(client_socket, &serverMsg);
        currID++;

        // receiving 
        recvPacket(client_socket, &clientMsg);
        clientID = clientMsg.id;

        /* if it is the answer to the previously sent message... */
        if ( clientMsg.label == ACTION_DONE && clientMsg.ans_id == (currID - 1) )
        {
            /* if its an "atomic" (one-packet message)... */
            if ( clientMsg.order == -1 )
            {
                strcpy(player2.name, clientMsg.content);

                /* if the name has the right syntax... */
                if ( player2.name[0] != '\n' || player2.name[0] != '\0' )
                {
                    fillPacket(&serverMsg, CORRECT, currID, NO_ANS_ID,
                                 LAST, NO_ORDER, "input username");
                    sendPacket(client_socket, &serverMsg);
                    currID++;
                }
            }
            /* non-atomic messages not supported yet */
            else
            {
                strcpy(player2.name, "enemy");
                printf("List of packets not supported!\n");
            }
        } else
        {
            /* Missing answer to ACTION */
            fillPacket(&serverMsg, REPEAT, currID, clientMsg.ans_id, LAST, 
                        NO_ORDER, NO_CONTENT);
            
            sendPacket(client_socket, &serverMsg);
            currID++;

        }
    }while ( ( clientMsg.ans_id != (currID - 1) ) || ( player2.name[0] == '\n') ||
            ( player2.name[0] == '\0' ) );


    /* ----------------------------------- GAME SETUP --------------------------------- */

    clearScreen();
    printf("Great, not let's setup the game...\n\n");

    /* setting map dimensions */
    player2.attackMap.dims.x = player2.defenceMap.dims.x = player1.attackMap.dims.x = player1.defenceMap.dims.x = MAP_WIDTH;
    player2.attackMap.dims.y = player2.defenceMap.dims.y = player1.attackMap.dims.y = player1.defenceMap.dims.y = MAP_WIDTH;

    /* making maps empty */
    empty(&(player1.attackMap));
    empty(&(player1.defenceMap));

    empty(&(player2.attackMap));
    empty(&(player2.defenceMap));

    /* setting some default values */
    player1.winner = player2.winner = 0;

    player1.shipNumber = player2.shipNumber = DEFAULT_SHIP_NUM;

    initDefaultArmy(&defaultArmy);

    /* Now player1 place its ships */
    printf("%s, it's time to place your ships!\n", player1.name);
    printf("When your are ready, press enter... ");
    fflush(stdin);
    (void) getch_();

    playerArmySetup(&player1, defaultArmy);

    numAttempts = 0;
    do
    {
        fillPacket(&serverMsg, ACTION, currID, -1, 1, -1, "input ship");

        sendPacket(client_socket, &serverMsg);
        currID++;

        recvPacket(client_socket, &clientMsg);
        // NECESSARIO AVERE UN SISTEMA DI PACCHETTI NON-ATOMIC


    } while ( clientMsg.ans_id != (currID - 1) && numAttempts < MAX_SEND_ATTEMPTS );

    close(server_socket);

    return 0;
}

int playGuestLAN(MenuData data)
{
    Player localPlayer, oppPlayer;

    Army defaultArmy;
    GameSettings curSettings;

    DataPacket serverMsg, localMsg;
    int contentBuf[MAX_PACKETS * CHUNK_SIZE];

    int currID;
    int serverID;
    int numAttempts;
    int to_repeat;

    int local_socket;
    int addr_len = sizeof(local_socket);
    struct sockaddr_in server_address;
    int result;

    local_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    errno = 0;

    result = pconnect(local_socket, (struct sockaddr *) &server_address);

    if ( errno == OTHER_FAIL )
    {
        printf("Unable to connect to server. Press enter to go back\n");
        (void) getch_();
        (void) getch_();
        return OTHER_FAIL;
    }
    else if ( errno == PROTOCOL_FAIL )
    {
        printf("Connection protocol failed. Exiting ...\n");
        return PROTOCOL_FAIL;
    }


    /* ------------------------------ PLAYERS' NAMES INPUT ---------------------------- */
    currID = 1;
    do
    {
        clearScreen(); 

        printf("Please input your name \n -> ");
        fgets(localPlayer.name, MAX_NAME_LENGTH, stdin);
        printf("\n");

    } while(localPlayer.name[0] == '\n' && localPlayer.name[0] != '\0');

    filterNewLine(localPlayer.name);

    do
    {
        to_repeat = 0;
        recvPacket(local_socket, &serverMsg);
        serverID = serverMsg.id;
        if ( serverMsg.label != ACTION || strcmp(serverMsg.content, "input username") != 0)
            to_repeat = 1;
        else
        {
            fillPacket(&localMsg, ACTION_DONE, currID, serverID, LAST, NO_ORDER, localPlayer.name);
            currID++;

            sendPacket(local_socket, &localMsg);
            currID++;

            recvPacket(local_socket, &serverMsg);

            if ( serverMsg.label != CORRECT && strcmp(serverMsg.content, "input username"))
                to_repeat = 1;
        }
        
    } while(to_repeat == 1);
    
    printf("Username approved\n");
    return 0;
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
