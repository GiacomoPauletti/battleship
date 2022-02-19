#include "game.h"

Coordinate placeBomb(Player *player);

void playerArmySetup(Player* player, Army gameArmy)
{
    int playerDone;
    /* variable used to check whether user placed all its ships and it's ready to play */
    char input;
    /* user input is stored here */
    int inputNumber, currentNumber;
    /* if the input is numeric is saved into inputNumber for just 1 loop cycle,
     * currentNumber instead keep this number until a new one is input by the user */
    int shipCounter;
    /* counts the number of placed ships */
    int armyDone[gameArmy.shipNum];
    /* boolean array. Each element is 1 if the respectively indexed ship has been placed */
    Coordinate cursor;
    /* user cursor over the map */
    Coordinate backupCursor;
    /* used to store previous cursor position */
    int backupNumber;
    /* used to store previous currentNumber value */
    int shipCursor;
    /* cursor used to iterate through army ships */
    int curLength, curShipCounter;
    /* used in "case 'i'" */
    int rowCursor, colCursor;

    char buffer[400];

    player -> shipNumber = gameArmy.shipNum;

    for ( shipCursor = 0; shipCursor < gameArmy.shipNum; shipCursor++)
    {
        armyDone[shipCursor] = 0;
        player -> ships[shipCursor].hitCounter = 0;
    }

    cursor.x = cursor.y = -1;
    /* default values for cursor */

    currentNumber = -1;
    /* currentNumber is set to -1 because no ship has been chosen yet */
    shipCounter = 0;
    playerDone = 0;
    while ( playerDone == 0 )
    {
        clearScreen();
        printf("\n");
        printf("%s, please place your army\n", player -> name);
        printf("Type 'i' for help and information on you army\n");
        printf("You placed %d ships until now", shipCounter);
        printMap( player -> defenceMap );

        input = getch_();

        inputNumber = input - '0';
        if ( inputNumber >= 0 && inputNumber < DEFAULT_SHIP_NUM )
        /* if user input a valid number ... */
        {
            /* then select the ship and place it (if it is possible) */
            currentNumber = inputNumber; 

            

            if ( !armyDone[inputNumber])
            {
                if ( checkPosValidity(player -> defenceMap, gameArmy.ships[inputNumber]) != 1)
                {
                    clearScreen();
                    printf("\n");
                    printCenter("Cannot place the ship because it overlaps with another one.\n");
                    printCenter("Try to move the ships placed close to the middle in another place\n");
                    printCenter("Press 'k' to continue...\n");
                    while ( getch_() != 'k' );

                    if ( cursor.x != -1 )
                    {
                        cursor.x = backupCursor.x;
                        cursor.y = backupCursor.y;
                        currentNumber = backupNumber; 
                    }
                }
                else
                {
                    /* if it has already been placed, there is no need to place it again */
                    placeShip(&(player -> defenceMap), gameArmy.ships[inputNumber]);
                    /* storing or restoring default position */
                    player -> ships[inputNumber] = gameArmy.ships[inputNumber];

                    armyDone[inputNumber] = 1;
                    shipCounter++;

                    if ( cursor.x != -1 )
                    {
                        backupCursor.x = cursor.x;
                        backupCursor.y = cursor.y;
                        backupNumber = currentNumber;
                    }

                    cursor.x = gameArmy.ships[inputNumber].points[0].x;
                    cursor.y = gameArmy.ships[inputNumber].points[0].y;
                }
            }
            else 
            // if the ship is already in the map ...
            {

                //... there is no need for placing it again.
                //This means that no position check will be made.
                //The unique action required is moving the cursor to the ship
                if ( cursor.x != -1 )
                {
                    backupCursor.x = cursor.x;
                    backupCursor.y = cursor.y;
                    backupNumber = currentNumber;
                }

                cursor.x = gameArmy.ships[inputNumber].points[0].x;
                cursor.y = gameArmy.ships[inputNumber].points[0].y;
            }


            inputNumber = -1;


        }else if ( currentNumber >= 0 )
        {
            if (input != '\n')
            {

                switch (input)
                {
                        /* 'w', 'd', 'a', 's' are used for moving the ship ('w' is used to move upside) */
                        /* 'r' is used to rotate anti-clockwise the ship */
                        /* 'k' is used to exit from the ship placement phase (if all ships have been placed) */
                        /* '-' is used to remove from the map the currently selected ship */
                        case 'w':

                            if ( checkMovValidity(player -> defenceMap, player -> ships[currentNumber], 0, -1) )
                            {
                                unplaceShip(&(player -> defenceMap), player -> ships[currentNumber]);

                                moveShip(&(player -> ships[currentNumber]), 0, -1);
                                cursor.y += -1;
                                placeShip(&(player -> defenceMap), player -> ships[currentNumber]);

                            }

                            break;
                        case 'd':
                            if ( checkMovValidity(player -> defenceMap, player -> ships[currentNumber], 1, 0) )
                            {
                                unplaceShip(&(player -> defenceMap), player -> ships[currentNumber]);

                                moveShip(&(player -> ships[currentNumber]), 1, 0);
                                cursor.x += 1;

                                placeShip(&(player -> defenceMap), player -> ships[currentNumber]);
                            }
                            break;
                        case 's':
                            if ( checkMovValidity(player -> defenceMap, player -> ships[currentNumber], 0, 1) )
                            {
                                unplaceShip(&(player -> defenceMap), player -> ships[currentNumber]);

                                moveShip(&(player -> ships[currentNumber]), 0, 1);
                                cursor.y += 1;

                                placeShip(&(player -> defenceMap), player -> ships[currentNumber]);
                            }
                            break;
                        case 'a':
                            if ( checkMovValidity(player -> defenceMap, player -> ships[currentNumber], -1, 0) )
                            {
                                unplaceShip(&(player -> defenceMap), player -> ships[currentNumber]);

                                moveShip(&(player -> ships[currentNumber]), -1, 0);
                                cursor.x += -1;

                                placeShip(&(player -> defenceMap), player -> ships[currentNumber]);
                            }
                            break;
                        
                        case 'r':
                            if ( checkACRotValidity(player -> defenceMap, player -> ships[currentNumber], player -> ships[currentNumber].points[0]) )
                            {
                                unplaceShip(&(player -> defenceMap), player -> ships[currentNumber]);

                                rotateACShip(&(player -> ships[currentNumber]), player -> ships[currentNumber].points[0]);

                                placeShip(&(player -> defenceMap), player -> ships[currentNumber]);
                            }
                            break;

                        case '-':
                            unplaceShip(&(player -> defenceMap), player -> ships[currentNumber]);

                            /* restoring default position */
                            //player -> ships[currentNumber] = gameArmy.ships[currentNumber];

                            shipCounter--;

                            armyDone[currentNumber] = 0;
                            break;

                        case 'k':
                            if ( shipCounter == gameArmy.shipNum ) playerDone = 1;
                            break;

                        default:
                            break;
                }

            }
        }

        if ( input == 'i' )
        {
            clearScreen();
            sprintf(buffer, "HOW TO PLACE:\n"
                "[0 ... %d]: select the corresponding ship\n"
                "[w,a,s,d]: move selected ship around the map\n"
                "[r]: rotate the ship\n"
                "[-]: remove ship form map\n", gameArmy.shipNum);
            MultiPrintCenter(buffer);

            printCenter("If something goes wrong and you want to kill the program, use ctrl + C\n");
            printf("\n\n\n");

            /*
            printf("These are the ships you can place: \n");
            curLength = gameArmy.ships[0].length;
            curShipCounter = 1;
            for ( shipCursor = 1; shipCursor < gameArmy.shipNum; shipCursor++ )
            {
                if ( gameArmy.ships[shipCursor].length != curLength )
                {
                    printf("Length: %d, Number of ships: %d, Indexes: [%d ... %d]\n", curLength, curShipCounter, shipCursor - curShipCounter, shipCursor - 1);
                    curLength = gameArmy.ships[shipCursor].length;
                    curShipCounter = 0;
                }
            }
            */

            printf("\n\n");
            printCenter("When done press 'k' and then enter...\n");
            while ( getch_() != 'k' );

        }

        
    } // end of while [ while( playerDone == 0 ) ]

    clearScreen();
    printf("\n\n");
    printCenter("When done press 'k' and then enter...\n");
    while ( getch_() != 'k' );
}

int localGameHandler(Player *player1, Player *player2)
{
    Coordinate cursor;
    /* cursor used by the user to place the bomb */
    int shipCursor;
    /* used to iterate through player2 ships */
    int pointCursor;
    /* used to iterate through player2 ship points */
    int found, isSunk, result;

    cursor = placeBomb(player1);


    clearScreen();
    printf("\n\n");
    result = isShipHitted(player2, cursor);
    if ( getFromMap(player1 -> attackMap, cursor) == HIT_SHIP_CHAR )
    {
        printCenter("You already hitted this!!\n");
    }
    else if ( result >= 1 )
    {
        MultiPrintCenter("\
d8888b.  .d88b.   .d88b.  .88b  d88. \n\
88  `8D .8P  Y8. .8P  Y8. 88'YbdP`88 \n\
88oooY' 88    88 88    88 88  88  88 \n\
88~~~b. 88    88 88    88 88  88  88 \n\
88   8D `8b  d8' `8b  d8' 88  88  88 \n\
Y8888P'  `Y88P'   `Y88P'  YP  YP  YP");
        printf("\n\n\n");

        if ( result == 1 )
            printCenter("You HITTED a ship\n");
        else if ( result == 2 )
            printCenter("You HITTED and SUNK a ship\n");

        addToMap(&(player1 -> attackMap), cursor, HIT_SHIP_CHAR);
    }

    printf("\n\n");
    printCenter("When done press 'k' and then enter...");
    while( getch_() != 'k' );
    fflush(stdin);

    return isSunk;
}

// host is attacking 
int hostGameHandler(Player *attacker, Player *defender)
{
    Coordinate cursor;
    /* cursor used by the user to place the bomb */
    int shipCursor;
    /* used to iterate through player2 ships */
    int pointCursor;
    /* used to iterate through player2 ship points */
    int found, isSunk;

    char input;
    /* player input */

    DataPacket serverMsg, clientMsg;
    char bombCoords[CHUNK_SIZE];
    char attackResult1[CHUNK_SIZE], attackResult2[CHUNK_SIZE];
    int currID;
    currID = 0;

    // placing the bomb
    printf("%s, it's your turn: \n", attacker -> name);
    cursor = placeBomb(attacker);

    // asking guest for attack result
    sprintf(bombCoords, "%d,%d", cursor.x, cursor.y);
    fillPacket(&serverMsg, ACTION, currID, NO_ANS_ID, LAST, NO_ORDER, bombCoords);
    sendPacket(gclient_socket, &serverMsg);

    recvPacket(gclient_socket, &clientMsg);
    sscanf(clientMsg.content, "%s %s", attackResult1, attackResult2);

    clearScreen();
    isSunk = 0;
    if ( strcmp(attackResult1, "hitted") == 0 )
    {
        if ( getFromMap(attacker -> attackMap, cursor) == HIT_SHIP_CHAR )
        {

            printCenter("You already hitted this!!");
        }
        else // if hitted ship has not been hitted there yet
        {

            MultiPrintCenter("\
    d8888b.  .d88b.   .d88b.  .88b  d88. \n\
    88  `8D .8P  Y8. .8P  Y8. 88'YbdP`88 \n\
    88oooY' 88    88 88    88 88  88  88 \n\
    88~~~b. 88    88 88    88 88  88  88 \n\
    88   8D `8b  d8' `8b  d8' 88  88  88 \n\
    Y8888P'  `Y88P'   `Y88P'  YP  YP  YP");
            printf("\n\n\n");

            if ( strcmp(attackResult2, "sunk") == 0 )
            {
                printCenter("SHIP HITTED and SUNK\n");
                isSunk = 1;
            }
            else printCenter("SHIP HITTED but nothing else\n");
        }

        addToMap(&(attacker -> attackMap), cursor, HIT_SHIP_CHAR);
    }
    else
    {
        printCenter("YOU HITTED WATER\n");
    }

    return isSunk;
}

/* Used to handle guest attack in LAN match. 
 * Runs on host machine. */
int guestGameHandler(Player *onlinePlayer, Player *localPlayer)
{

    Coordinate cursor;
    /* cursor used by the user to place the bomb */
    int shipCursor;
    /* used to iterate through player2 ships */
    int pointCursor;
    /* used to iterate through player2 ship points */
    int found, isSunk;
    /* contains information about attack result.
     * Format: hitted/already_hitted/water sunk/not_sunk/_
     * Second column used only if first option is hitted, otherwise its content
     * is _ 
     */
    char attackResult[CHUNK_SIZE];
    char buffer[300];

    int result;
    int to_repeat;
    /* if the communication with server failed */

    DataPacket serverMsg, clientMsg;
    int currID;
    currID = 0;

    do 
    {
        to_repeat = 0;
        // asking player to place the bomb
        fillPacket(&serverMsg, ACTION, currID, NO_ANS_ID, LAST, NO_ORDER, "place the bomb");
        sendPacket(gclient_socket, &serverMsg);

        // player placed the bomb at given coordinates
        // coordinates given with the following format:
        //  x,y
        recvPacket(gclient_socket, &clientMsg);

        if ( clientMsg.label == ACTION_DONE )
        {
            if ( sscanf(clientMsg.content, "%d,%d", &(cursor.x), &(cursor.y)) != 2 )
            {
                printf("Invalid coordinates\n");
                to_repeat = 1;
                exit(1);
            }
            else
            {

                printf("\n\n");

                //checking attack result  
                isSunk = 0;
                result = isShipHitted(localPlayer, cursor);
                if ( result == 0 )
                {
                    strcpy(attackResult, "water _");
                
                    printCenter("Enemy hitted water\n");
                }
                else if ( result == 1 )
                {
                    strcpy(attackResult, "hitted not_sunk");

                    addToMap(&(onlinePlayer -> attackMap), cursor, HIT_SHIP_CHAR);

                    sprintf(buffer, "Enemy hitted your ship at (%d,%d)\n", cursor.x, cursor.y);
                    printCenter(buffer);
                } 
                else if ( result == 2 )
                {
                    strcpy(attackResult, "hitted sunk");

                    addToMap(&(onlinePlayer -> attackMap), cursor, HIT_SHIP_CHAR);

                    sprintf(buffer, "Enemy hitted and sunk your ship at (%d,%d)\n", cursor.x, cursor.y);
                    printCenter(buffer);
                }

            } 

            // sending attack results to client
            fillPacket(&serverMsg, CORRECT, currID, clientMsg.ans_id, LAST, NO_ORDER, 
                        attackResult);
            currID++;
            sendPacket(gclient_socket, &serverMsg);

        }
        else //if not clientMsg.label == ACTION_DONE
            to_repeat = 1;

    } while ( to_repeat == 1 );


    return isSunk;
}

/* Used to handle client side the game actions. 
 * Runs on guest machine. */
int localGuestGameHandler(Player *localPlayer, Player *oppPlayer)
{
    int gameEnded;
    /* if game ends, the function terminates */

    int shipCursor, pointCursor;
    /* used to iterate through ships and ship points */
    int result;

    int to_repeat;

    DataPacket serverMsg, localMsg;
    /* used to communicate with server */

    Coordinate cursor;
    /* contains coordinates of bomb (for both host and local player, one at time) */

    char bombResult[CHUNK_SIZE];
    char attackResult1[CHUNK_SIZE];
    char attackResult2[CHUNK_SIZE];
    char buffer[300];
    /* used to format strings and handle results properly */

    int currID;
    /* pacekt ids */
    currID = 0;

    clearScreen();

    gameEnded = 0;  
    while ( gameEnded == 0 )
    {

        printCenter("Waiting for opponent to attack...");
        
        /* packets should be as follow:
         *  1) ACTION (from host) which is attacking
         *  2) ACTION_DONE (from guest) telling attack results
         *  3) ACTION (from host) asking guest to attack
         *  4) ACTION_DONE (from guest) saying bomb coordinates
         *  5) CORRECT (from host) telling attack results
         * 
         * If game ends ACTION messages are replaced by EOC and in message 
         * content there is written the winner */


        // local player is defending
        do
        {
            // 1) ACTION
            recvPacket(glocal_socket, &serverMsg);

            // if game ended
            if ( serverMsg.label == EOC )
            {
                clearScreen();
                printf("\n\n");
                if ( strcmp(serverMsg.content, "guest win") == 0 )
                {
                    gameWinWriting();
                }
                else
                {
                    gameLostWriting();
                }
                
                gameEnded = 1;
                break;
            }

        } while ( serverMsg.label != ACTION );
        // packets that are different from ACTION or EOC are ignored 
        
        // exiting from loop if game ended
        if ( gameEnded == 1 ) break;

        // checking whether host hitted (and/or sunk) a ship or not
        clearScreen();
        printf("\n\n");
        sscanf(serverMsg.content, "%d,%d", &(cursor.x), &(cursor.y));
        result = isShipHitted(localPlayer, cursor);
        if ( result == 0 )
        // hitted water
        {
            fillPacket(&localMsg, ACTION_DONE, currID, serverMsg.id, LAST, 
            NO_ORDER, "water _");

            printCenter("Enemy hitted WATER\n");
        }
        else if ( result == 1 )
        // hitted ship but not sunk
        {
            fillPacket(&localMsg, ACTION_DONE, currID, serverMsg.id, LAST, 
            NO_ORDER, "hitted not_sunk");
            addToMap(&(localPlayer -> defenceMap), cursor, HIT_SHIP_CHAR);

            sprintf(buffer, "Enemy HITTED your ship at (%d,%d)\n", cursor.x, cursor.y);
            printCenter(buffer);
        }
        else if ( result == 2 )
        // hitted and sunk ship
        {
            fillPacket(&localMsg, ACTION_DONE, currID, serverMsg.id, LAST, 
            NO_ORDER, "hitted sunk");
            addToMap(&(localPlayer -> defenceMap), cursor, HIT_SHIP_CHAR);

            sprintf(buffer, "Enemy HITTED and SUNK your ship at (%d,%d)\n", cursor.x, cursor.y);
            printCenter(buffer);
        }


        // 2) ACTION_DONE
        sendPacket(glocal_socket, &localMsg);
        currID++;

        printf("\n\n\n\n");
        printCenter("When done press 'k' and then enter...");
        printf("\n");
        while ( getch_() != 'k' );

        //local player is attacking
        do
        {

            // 3) ACTION
            recvPacket(glocal_socket, &serverMsg);

            // if game ended, EOC is received
            if ( serverMsg.label == EOC )
            {
                clearScreen();
                printf("\n\n");
                if ( strcmp(serverMsg.content, "guest win") == 0 )
                    gameWinWriting();
                else 
                    gameLostWriting();
                                
                gameEnded = 1;
                break;
            }

        } while ( serverMsg.label != ACTION );

        if ( gameEnded == 1 ) break;

        clearScreen();
        printf("%s, it's your turn: \n", localPlayer -> name);

        // player places the bomb
        cursor = placeBomb(localPlayer);
        sprintf(bombResult, "%d,%d", cursor.x, cursor.y);
        fillPacket(&localMsg, ACTION_DONE, currID, serverMsg.ans_id, LAST, NO_ORDER, bombResult);

        // 4) ACTION_DONE
        sendPacket(glocal_socket, &localMsg);
        currID++;

        do
        {
            // 5) CORRECT 
            recvPacket(glocal_socket, &serverMsg);
        } while ( serverMsg.label != CORRECT );

        clearScreen();
        sscanf(serverMsg.content, "%s %s", attackResult1, attackResult2);

        if ( strcmp(attackResult1, "hitted") == 0 )
        // ship hitted
        {
            
            MultiPrintCenter("\
    d8888b.  .d88b.   .d88b.  .88b  d88. \n\
    88  `8D .8P  Y8. .8P  Y8. 88'YbdP`88 \n\
    88oooY' 88    88 88    88 88  88  88 \n\
    88~~~b. 88    88 88    88 88  88  88 \n\
    88   8D `8b  d8' `8b  d8' 88  88  88 \n\
    Y8888P'  `Y88P'   `Y88P'  YP  YP  YP");
            printf("\n\n\n");

            if ( strcmp(attackResult2, "sunk") == 0 )
            // ship sunk
            {
                printCenter("SHIP HITTED and SUNK\n");
            } else printCenter("SHIP HITTED but nothing else\n");

            addToMap(&(localPlayer -> attackMap), cursor, HIT_SHIP_CHAR);
        } 
        else // water hitted
        {
            printCenter("YOU HITTED WATER\n");
        }
        printf("\n\n\n");

    }

    return 0;
}

/* Used to make player place the bomb
 * RETURN VALUE:
 * returns where the bomb has been placed
 */
Coordinate placeBomb(Player *player)
{
    MapWrap *curMap;
    Coordinate cursor;
    char tempSymbol, input;
    int playerDone;

    curMap = &(player -> attackMap);
    /* default current map */

    cursor.x = player -> attackMap.dims.x / 2; 
    cursor.y = player -> attackMap.dims.y / 2;
    /* initial default coordinates of cursor */

    tempSymbol = getFromMap(*curMap, cursor);
    addToMap(curMap, cursor, CURSOR_CHAR);

    /* 'w', 'd', 'a', 's' are used for moving the bomb cursor around the map */
    /* 'k' is used to drop the bomb */
    /* 'i' is used to see game commands */
    /* 'm' is used to switch between attack and defence map */

    playerDone = 0;
    while ( playerDone == 0)
    {
        #if !defined(DEBUG_GAME) && !defined(DEBUG_ALL)
        clearScreen();
        #endif

        printf("\n\n");
        if (curMap == &(player -> attackMap))
            printCenter("ATTACK MAP");
        else
            printCenter("DEFENCE MAP");

        printMap(*curMap);
        printf("[%s] Type 'i' for help and information on the game\n", player -> name);
    

        input = getch_();

        if ( curMap == &(player -> attackMap) )
        {
            switch (input)
            {
                case 'w':
                    if (cursor.y - 1 >= 0)
                    {
                        addToMap(curMap, cursor, tempSymbol);
                        /* before moving, the cursor is removed and replaced with what
                        * there was before cursor moved on it */

                        cursor.y -=1;
                        /* moving the cursor */
                        tempSymbol = getFromMap(*curMap, cursor);
                        /* saving replaced symbol to put it back when cursor moves again */

                        addToMap(curMap, cursor, CURSOR_CHAR);
                        /* adding cursor to the new position */

                    }
                    break;

                case 'd':
                    if (cursor.x + 1 < player -> attackMap.dims.x)
                    {
                        addToMap(curMap, cursor, tempSymbol);

                        cursor.x +=1;

                        tempSymbol = getFromMap(*curMap, cursor);
                        addToMap(curMap, cursor, CURSOR_CHAR);

                    }
                    break;

                case 's':
                    if (cursor.y + 1 < player -> attackMap.dims.y)
                    {
                        addToMap(curMap, cursor, tempSymbol);

                        cursor.y +=1;

                        tempSymbol = getFromMap(*curMap, cursor);
                        addToMap(curMap, cursor, CURSOR_CHAR);

                    }
                    break;

                case 'a':
                    if (cursor.x - 1 >= 0)
                    {
                        addToMap(curMap, cursor, tempSymbol);

                        cursor.x -=1;

                        tempSymbol = getFromMap(*curMap, cursor);
                        addToMap(curMap, cursor, CURSOR_CHAR);

                    }
                    break;

                case 'k':
                    if ( getFromMap(*curMap, cursor) != HIT_SHIP_CHAR )
                    {
                        addToMap(curMap, cursor, tempSymbol);
                        playerDone = 1;
                    }
                    break;

                case 'i':
                    clearScreen();
                    printCenter("HOW TO PLAY");
                    printf("\n");
                    printCenter("[w,a,s,d]: move the cursor around the map");
                    printCenter("[k] confirms bomb location and ends the turn");
                    printCenter("[m] used to switch between defence and attack map");
                    printf("\n\n");
                    printCenter("When done press 'k' and then enter");
                    printf("\n\n\n");;
                    while ( getch_() != 'k');
                    break;

                case 'm':
                    curMap = &(player -> defenceMap);
                    break;

                default:
                    break;
            }

        } // end of "if ( curMap == &(player1 -> attackMap) )"            
        else // if defence map is selected
        {
            switch (input)
            {
                case 'i':
                    printCenter("HOW TO PLAY");
                    printf("\n");
                    printCenter("[w,a,s,d]: move the cursor around the map");
                    printCenter("[k] confirms bomb location and ends the turn");
                    printCenter("[m] used to switch between defence and attack map");
                    printf("\n\n");
                    printCenter("When done press 'k' and then enter");
                    printf("\n\n\n");;
                    while ( getch_() != 'k' );
                    break;
                case 'm':
                    curMap = &(player -> attackMap);
                    break;
                
                default:
                    break;
            }
        }

    } // end of "while ( playerDone == 0)"

    return cursor;
}

/* checks whether any ship placed by player is hitted.
/* RETURN VALUE:
 *      - 0 if hitted water
 *      - 1 if hitted ship but not sunk
 *      - 2 if hitted ship and sunk
*/
int isShipHitted(Player *player, Coordinate point)
{

    int isSunk;
    int found, shipCursor, pointCursor;
    found = 0;

    if ( player -> defenceMap.map[point.y][point.x] == SAFE_SHIP_CHAR ||
        player -> defenceMap.map[point.y][point.x] == HIT_SHIP_CHAR )
    {
        // checking if ship is sunk and updating ships
        for ( shipCursor = 0; found == 0 && shipCursor < player -> shipNumber; shipCursor++ )
        {
            for ( pointCursor = 0; found == 0 && pointCursor < player -> ships[shipCursor].length; pointCursor++ )
            {
                #if defined(DEBUG_GAME) || defined(DEBUG_ALL)
                printf("%d | %d\n", player -> ships[shipCursor].points[pointCursor].x, cursor.x);
                printf("%d | %d\n", player -> ships[shipCursor].points[pointCursor].y, cursor.y);
                #endif
                
                // current ship is the hitted one
                if ( ( player -> ships[shipCursor].points[pointCursor].x == point.x) && 
                    ( player -> ships[shipCursor].points[pointCursor].y == point.y) )
                    {
                        #if defined(DEBUG_GAME) || defined(DEBUG_ALL)
                        printf("FOUND, before updating, hitCounter is: %d\n", player2 -> ships[shipCursor].hitCounter);
                        #endif

                        found = 1;
                        player -> ships[shipCursor].hitCounter++;
                        
                        if ( player -> ships[shipCursor].hitCounter == player -> ships[shipCursor].length )
                        // ship is sunk
                        {
                            return 2;
                        }

                    }
            }
        }
        return 1;
    }

    return 0;
}