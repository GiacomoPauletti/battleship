#include "ship.h"
#include <stdio.h>
#include <stdlib.h>

int SHIP_NUMBER = DEFAULT_SHIP_NUM;


void initDefaultArmy(Army *defaultArmy)
{
    int lengthCursorA, shipCursorB, pointCursor;
    int shipLength;
    int shipCounter;

    shipCounter = 0;

    for ( lengthCursorA = 1; lengthCursorA <= 4; lengthCursorA++ )
    {

        for ( shipCursorB = 0; shipCursorB <= 4 - lengthCursorA; shipCursorB++)
        {
            defaultArmy -> ships[shipCounter].length = lengthCursorA;
            
            for ( pointCursor = 0; pointCursor < lengthCursorA; pointCursor++)
            {
                defaultArmy -> ships[shipCounter].points[pointCursor].x = MAP_WIDTH / 2 - 1;
                defaultArmy -> ships[shipCounter].points[pointCursor].y = 2 + pointCursor;
            }

            shipCounter++;

        }

    }
}



void findShip(Map map, Coordinate point, Ship *ship)
{
    int pointCursor, deltasCursor;

    Coordinate deltas[4] =
    {
        {.x = 0, .y=-1},
        {.x = 1, .y=0},
        {.x = 0, .y=1},
        {.x = -1, .y=0},

    };

    Coordinate newPoint;
    int isNewPoint;

    for ( deltasCursor = 0; deltasCursor < 4; deltasCursor++ )
    {
        newPoint.x = point.x + deltas[deltasCursor].x;  
        newPoint.y = point.y + deltas[deltasCursor].y;  

        if ( ( newPoint.x >= 0 && newPoint.x < MAP_WIDTH ) && ( newPoint.y >= 0 && newPoint.y < MAP_HEIGHT ) )
        /* not accepting points that are not in the map range */
        {

            if ( getFromMap(map, newPoint) == SAFE_SHIP_CHAR )
            {
                isNewPoint = 1;
                for (pointCursor = 0; pointCursor < ship -> length && isNewPoint == 1; pointCursor++)
                {
                    if ( ( ship -> points[pointCursor].x == newPoint.x ) &&
                        ( ship -> points[pointCursor].y == newPoint.y ) )
                        isNewPoint = 0;
                }

                if ( isNewPoint == 1 )
                {
                    ship -> points[ship -> length] = newPoint;
                    ship -> length++;

                    findShip(map, newPoint, ship);
                }
            }

        }

    }

}

int isLegal(Ship ship)
{
    Map map;
    Ship checkedShip;

    if ( ship.length == 0 ) return 0;
    /* empty ships are not allowed */

    checkedShip.points[0] = ship.points[0];
    checkedShip.length = 1;

    mAddToMap(map, ship.points, ship.length, SAFE_SHIP_CHAR);
    /* creating and adding to map the ship, so that findShip finds
     * all consecutive points of the drawn ship
     */

    findShip(map, ship.points[0], &checkedShip);

    if ( checkedShip.length != ship.length ) return 0;

    int cursorShip, cursorCheckShip;
    int isLegal_, found;

    isLegal_ = 1;

    /* the following code checks if every point of the checked ship is a point of the original
     * ship.
     * It has already been checked the fact that two ships have same length so it must 
     * happen either all points matches or at least one point is not present.
     * 
     * If one point is not found then the ship must not be legal. 
     * 
     * Points cannot be redundant because findShip checks whether one point has already been 
     * found before adding it to the ship.
     */
    for ( cursorCheckShip = 0; cursorCheckShip < ship.length && isLegal_ == 1; cursorCheckShip++ )
    {
        found = 0;
        for ( cursorShip = 0; cursorShip < ship.length && found == 0; cursorShip++ )
        {
            if ( ( checkedShip.points[cursorCheckShip].x == ship.points[cursorShip].x ) && 
                 ( checkedShip.points[cursorCheckShip].y == ship.points[cursorShip].y ))
                 found = 1;
        }
        if (found == 0) isLegal_ = 0;
    }

    
    return isLegal_;
}

int isPlaceable(Map map, Ship ship)
{
    int cursor;
    int isPlaceable;

    isPlaceable = 1;
    for ( cursor = 0; cursor < ship.length && isPlaceable == 1; cursor++ )
    {
        if ( ( ship.points[cursor].y < 0 || ship.points[cursor].y >= MAP_HEIGHT ) ||
             ( ship.points[cursor].x < 0 || ship.points[cursor].x >= MAP_WIDTH ) )
             /* if the point is out of the map range, 0 will be returned */
            isPlaceable = 0;
        else if ( getFromMap(map, ship.points[cursor]) != EMPTY_CHAR )
            /* if the point is overlapping with an already filled point, 0 will be returned */
            isPlaceable = 0;

    }
    /* if every point is placeable, 1 will be returned */
    return isPlaceable;
}

int placeShip(Map map, Ship ship)
{
    int cursor;
    int validPosition;
    Coordinate point;
    
    /* if the ship is placeable, it is then placed */
    validPosition = isPlaceable(map, ship);
    if ( validPosition == 1)
    {
        for ( cursor = 0; cursor < ship.length; cursor++ )
        {
            point.x = ship.points[cursor].x;
            point.y = ship.points[cursor].y;

            addToMap(map, point, SAFE_SHIP_CHAR);

        }
    }

    return validPosition;
}

