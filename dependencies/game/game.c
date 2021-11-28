#include "game.h"

void playerArmySetup(Player* player, Army gameArmy)
{
    int shipCounter;
    int playerDone;
    char input;
    int inputNumber;

    Coordinate cursor;

    Ship selectedShip;

    shipCounter = 0;
    playerDone = 0;
    while ( playerDone == 0 )
    {
        #if defined(__linux__)
        input = getchar();        
        #else
        input = getch();
        #endif

        inputNumber = input - '0';
        if ( inputNumber >= 0 && inputNumber < DEFAULT_SHIP_NUM )
        {
            selectedShip = gameArmy.ships[inputNumber];
            cursor.x = ( player -> defenceMap.dims.x ) / 2 - 1;
            cursor.y = ( player -> defenceMap.dims.y ) / 2 - 1;

            placeShip(player -> defenceMap, selectedShip);

        }
        else
        {
            switch (input)
            {
                    case 'w':
                        unplaceShip(player -> defenceMap, selectedShip);
                        moveShip(&selectedShip, 0, -1);
                        placeShip(player -> defenceMap, selectedShip);
                        break;
                    case 'd':
                        unplaceShip(player -> defenceMap, selectedShip);
                        moveShip(&selectedShip, 1, 0);
                        placeShip(player -> defenceMap, selectedShip);
                        break;
                    case 's':
                        unplaceShip(player -> defenceMap, selectedShip);
                        moveShip(&selectedShip, 1, 0);
                        placeShip(player -> defenceMap, selectedShip);
                        break;
                    case 'a':
                        unplaceShip(player -> defenceMap, selectedShip);
                        moveShip(&selectedShip, -1, 0);
                        placeShip(player -> defenceMap, selectedShip);
                        break;
                    
                    case 'r':
                        unplaceShip(player -> defenceMap, selectedShip);
                        rotateACShip(&selectedShip, selectedShip.points[0]);
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
