#include "game.h"

void playerArmySetup(Player* player, Army gameArmy)
{
    int playerDone;
    char input;
    int inputNumber, currentNumber;

    int shipCounter;
    int armyDone[gameArmy.shipNum];

    Coordinate cursor;


    currentNumber = -1;
    shipCounter = 0;
    playerDone = 0;
    while ( playerDone == 0 )
    {
        clearScreen();
        printMap( player -> defenceMap );

        #if defined(__linux__)
        input = getchar();
        #else
        input = getch();
        #endif

        inputNumber = input - '0';
        if ( inputNumber >= 0 && inputNumber < DEFAULT_SHIP_NUM )
        {
            currentNumber = inputNumber; 
            cursor.x = gameArmy.ships[inputNumber].points[0].x;
            cursor.x = gameArmy.ships[inputNumber].points[0].y;

            placeShip(&(player -> defenceMap), gameArmy.ships[inputNumber]);

            if ( !armyDone[inputNumber])
            {
                armyDone[inputNumber] = 1;
                shipCounter++;
            }

            inputNumber = -1;

        }
        else if ( currentNumber >= 0 )
        {
            if (input != '\n')
            {

                switch (input)
                {
                        case 'w':

                            if ( checkMovValidity(player -> defenceMap, gameArmy.ships[currentNumber], 0, -1) )
                            {
                                unplaceShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);

                                moveShip(&(gameArmy.ships[currentNumber]), 0, -1);
                                cursor.y += -1;
                                placeShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);

                            }

                            break;
                        case 'd':
                            if ( checkMovValidity(player -> defenceMap, gameArmy.ships[currentNumber], 1, 0) )
                            {
                                unplaceShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);

                                moveShip(&(gameArmy.ships[currentNumber]), 1, 0);
                                cursor.x += 1;

                                placeShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);
                            }
                            break;
                        case 's':
                            if ( checkMovValidity(player -> defenceMap, gameArmy.ships[currentNumber], 0, 1) )
                            {
                                unplaceShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);

                                moveShip(&(gameArmy.ships[currentNumber]), 0, 1);
                                cursor.y += 1;

                                placeShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);
                            }
                            break;
                        case 'a':
                            if ( checkMovValidity(player -> defenceMap, gameArmy.ships[currentNumber], -1, 0) )
                            {
                                unplaceShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);

                                moveShip(&(gameArmy.ships[currentNumber]), -1, 0);
                                cursor.x += -1;

                                placeShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);
                            }
                            break;
                        
                        case 'r':
                            unplaceShip(&(player -> defenceMap), gameArmy.ships[currentNumber]);
                            rotateACShip(&(gameArmy.ships[currentNumber]), gameArmy.ships[currentNumber].points[0]);
                            break;

                        case 'k':
                            if ( shipCounter == gameArmy.shipNum ) playerDone = 1;
                            break;

                        default:
                            break;
                }

            }
        }

        
    }


}
