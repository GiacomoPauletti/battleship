#include "game.h"

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
    int shipCursor;
    /* cursor used to iterate through army ships */
    int curLength, curShipCounter;
    /* used in "case 'i'" */

    player -> shipNumber = gameArmy.shipNum;

    for ( shipCursor = 0; shipCursor < gameArmy.shipNum; shipCursor++)
    {
        armyDone[shipCursor] = 0;
        player -> ships[shipCursor].hitCounter = 0;
    }

    currentNumber = -1;
    /* currentNumber is set to -1 because no ship has been chosen yet */
    shipCounter = 0;
    playerDone = 0;
    while ( playerDone == 0 )
    {
        clearScreen();
        printf("%s, please place your army\n", player -> name);
        printf("type 'i' for help and information on you army\n");
        printf("You placed %d ships until now", shipCounter);
        printMap( player -> defenceMap );

        input = getch_();

        inputNumber = input - '0';
        if ( inputNumber >= 0 && inputNumber < DEFAULT_SHIP_NUM )
        /* if user input a valid number ... */
        {
            /* then select the ship and place it (if it is possible) */
            currentNumber = inputNumber; 
            cursor.x = gameArmy.ships[inputNumber].points[0].x;
            cursor.x = gameArmy.ships[inputNumber].points[0].y;


            if ( !armyDone[inputNumber])
            {
                /* if it has already been placed, there is no need to place it again */
                placeShip(&(player -> defenceMap), gameArmy.ships[inputNumber]);
                /* storing or restoring default position */
                player -> ships[inputNumber] = gameArmy.ships[inputNumber];

                armyDone[inputNumber] = 1;
                shipCounter++;
            }
            else placeShip(&(player -> defenceMap), player -> ships[inputNumber]);

            inputNumber = -1;

        }
        else if ( currentNumber >= 0 )
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
            printf("HOW TO PLACE:\n"
                "\t[0 ... %d]: select the corresponding ship\n"
                "\t[w,a,s,d]: move selected ship around the map\n"
                "\t[r]: rotate the ship \n"
                "\t[-]: remove ship form map \n", gameArmy.shipNum);

            printf("\n\n\n");

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

            printf("\n\n");
            printf("When done press 'k' and then enter...");
            while ( getch_() != 'k' );

        }

        
    } // end of while [ while( playerDone == 0 ) ]

}

int localGameHandler(Player *player1, Player *player2)
{
    MapWrap *curMap;
    /* current map opened by the player. Can be either attack map or defence map. */
    Coordinate cursor;
    /* cursor used by the user to place the bomb */
    char tempSymbol;
    /* temporary symbol unplaced by the cursor */
    int playerDone;
    /* when the player is done and selected the spot where to place the bomb */
    int shipCursor;
    /* used to iterate through player2 ships */
    int pointCursor;
    /* used to iterate through player2 ship points */
    int found, isSunk;

    char input;
    /* player input */

    curMap = &(player1 -> attackMap);
    /* default current map */

    cursor.x = player1 -> attackMap.dims.x / 2; 
    cursor.y = player1 -> attackMap.dims.y / 2;
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
        if (curMap == &(player1 -> attackMap))
            printf("\t\t\t\t\t\t ATTACK MAP\n");
        else
            printf("\t\t\t\t\t\t\t DEFENCE MAP\n");

        printMap(*curMap);
        printf("[%s] Type 'i' for help and information on the game\n", player1 -> name);
    

        input = getch_();

        if ( curMap == &(player1 -> attackMap) )
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
                    if (cursor.x + 1 < player1 -> attackMap.dims.x)
                    {
                        addToMap(curMap, cursor, tempSymbol);

                        cursor.x +=1;

                        tempSymbol = getFromMap(*curMap, cursor);
                        addToMap(curMap, cursor, CURSOR_CHAR);

                    }
                    break;

                case 's':
                    if (cursor.y + 1 < player1 -> attackMap.dims.y)
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
                    addToMap(curMap, cursor, tempSymbol);
                    playerDone = 1;
                    break;

                case 'i':
                    clearScreen();
                    printf("HOW TO PLACE:\n"
                        "\t[w,a,s,d]: move the cursor around the map\n"
                        "\t[k] confirms bomb location and ends the turn\n"
                        "\t[m] used to switch between defence and attack map\n");
                    printf("\n\n");
                    printf("When done press 'k' and then enter...");
                    while ( getch_() != 'k');
                    break;

                case 'm':
                    curMap = &(player1 -> defenceMap);
                    break;

                default:
                    break;
            }

        } // end of "if ( curMap == &(player1 -> attackMap) )"            
        else
        {
            switch (input)
            {
                case 'i':
                    printf("HOW TO PLACE:\n"
                        "\t[w,a,s,d]: move the cursor around the map\n"
                        "\t[k] confirms bomb location and ends the turn"
                        "\t[m] used to switch between defence and attack map");
                    printf("\n\n");
                    printf("When done press 'k' and then enter...");
                    while ( getch_() != 'k' );
                    break;
                case 'm':
                    curMap = &(player1 -> attackMap);
                    break;
                
                default:
                    break;
            }
        }

    } // end of "while ( playerDone == 0)"
    
    clearScreen();
    if ( ( player2 -> defenceMap.map[cursor.y][cursor.x] == SAFE_SHIP_CHAR ) && 
         ( player1 -> attackMap.map[cursor.y][cursor.x] != HIT_SHIP_CHAR ) )
    {
        printf("BOOOOM\n");
        printf("SHIP HITTED AND ...\n");

        addToMap(&(player1 -> attackMap), cursor, HIT_SHIP_CHAR);

        isSunk = 0;
        found = 0;
        for ( shipCursor = 0; found == 0 && shipCursor < player2 -> shipNumber; shipCursor++ )
        {
            
            for ( pointCursor = 0; found == 0 && pointCursor < player2 -> ships[shipCursor].length; pointCursor++ )
            {
                #if defined(DEBUG_GAME) || defined(DEBUG_ALL)
                printf("%d | %d\n", player2 -> ships[shipCursor].points[pointCursor].x, cursor.x);
                printf("%d | %d\n", player2 -> ships[shipCursor].points[pointCursor].y, cursor.y);
                #endif
                
                if ( (player2 -> ships[shipCursor].points[pointCursor].x == cursor.x) && 
                     (player2 -> ships[shipCursor].points[pointCursor].y == cursor.y) )
                     {
                        #if defined(DEBUG_GAME) || defined(DEBUG_ALL)
                        printf("FOUND, before updating, hitCounter is: %d\n", player2 -> ships[shipCursor].hitCounter);
                        #endif

                        found = 1;
                        player2 -> ships[shipCursor].hitCounter++;
                        
                        if ( player2 -> ships[shipCursor].hitCounter == player2 -> ships[shipCursor].length )
                        {
                            printf(" ... SHIP HAS BEEN SUNK!!");
                            isSunk = 1;
                        }

                     }
            }
        }
        if (!isSunk) printf("... unfortunately nothing else\n");
    } // end of "ship hit if statement" [if ( player2 -> defenceMap.map[cursor.y][cursor.x] == SAFE_SHIP_CHAR )]
    else if ( player1 -> attackMap.map[cursor.y][cursor.x] != HIT_SHIP_CHAR )
        printf("You already hitted this!!");
    else printf("Nope! You hitted water.\n");

    printf("\n\n");
    printf("When done press 'k' and then enter...");
    while( getch_() != 'k' );
    fflush(stdin);

    return isSunk;
}
