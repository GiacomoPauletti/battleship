#include "ship.h"
#include <stdio.h>
#include <stdlib.h>

int SHIP_NUMBER = DEFAULT_SHIP_NUM;


int initDefaultArmy(Army *defaultArmy)
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



void findShip(MapWrap map, Coordinate point, Ship *ship)
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

        if ( ( newPoint.x >= 0 && newPoint.x < map.dims.x ) && ( newPoint.y >= 0 && newPoint.y < map.dims.y ) )
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
    MapWrap map;
    Ship checkedShip;

    if ( ship.length == 0 ) return 0;
    /* empty ships are not allowed */

    checkedShip.points[0] = ship.points[0];
    checkedShip.length = 1;

    mAddToMap(&map, ship.points, ship.length, SAFE_SHIP_CHAR);
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

int isPlaceable(MapWrap map, Ship ship)
{
    int cursor;
    int isPlaceable;

    isPlaceable = 1;
    for ( cursor = 0; cursor < ship.length && isPlaceable == 1; cursor++ )
    {
        if ( ( ship.points[cursor].y < 0 || ship.points[cursor].y >= map.dims.y ) ||
             ( ship.points[cursor].x < 0 || ship.points[cursor].x >= map.dims.x ) )
             /* if the point is out of the map range, 0 will be returned */
            isPlaceable = 0;
        else if ( getFromMap(map, ship.points[cursor]) != EMPTY_CHAR )
            /* if the point is overlapping with an already filled point, 0 will be returned */
            isPlaceable = 0;

    }
    /* if every point is placeable, 1 will be returned */
    return isPlaceable;
}

int placeShip(MapWrap *map, Ship ship)
{
    int cursor;
    int validPosition;
    Coordinate point;
    

    /* if the ship is placeable, it is then placed */
    validPosition = isPlaceable(*map, ship);
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

int unplaceShip(MapWrap *map, Ship ship)
{
    int cursor;
    Coordinate point;
    
    // WARNING: no control is made to check if ship has legal points



    /* if the ship is placeable, it is then placed */
    for ( cursor = 0; cursor < ship.length; cursor++ )
    {
        point.x = ship.points[cursor].x;
        point.y = ship.points[cursor].y;


        addToMap(map, point, EMPTY_CHAR);

    }

    return 1;
}

int moveShip(Ship *ship, int deltaX, int deltaY)
{
    int pointCursor;
    for ( pointCursor = 0; pointCursor < ship -> length; pointCursor++ )
    {
        ship -> points[pointCursor].x += deltaX;
        ship -> points[pointCursor].y += deltaY;
    }


    return 1;
}

int checkMovValidity(MapWrap map, Ship ship, int deltaX, int deltaY)
{
    int cursor;
    int isMovValid;

    isMovValid = 1;
    for ( cursor = 0; cursor < ship.length && isMovValid == 1; cursor++ )
    {
        if ( ( ship.points[cursor].x + deltaX < 0 || ship.points[cursor].x + deltaX >= map.dims.x ) ||
             ( ship.points[cursor].y + deltaY < 0 || ship.points[cursor].y + deltaY >= map.dims.y ) )
             isMovValid = 0;
    }

    return isMovValid;
}


void rotateACShip(Ship *ship, Coordinate center)
{
    int cursor;
    int tempX;
    

    for ( cursor = 0; cursor < ship -> length; cursor++ )
    {
        tempX = ship -> points[cursor].x;
        ship -> points[cursor].x = center.x + (ship -> points[cursor].y - center.y);
        ship -> points[cursor].y = center.y + (center.x - tempX);

    }

    /* This 2 line of codes are better understandable with an example:
     *
     *               INPUT     ->     OUTPUT
     *              O O O 0                
     *              X                  X O
     *                                   O
     *                                   O
     *                                   0
     * 
     * The rotation center is marked with an X.
     * Let's consider the farthest point, marked with 0
     * We can see that in the input map:
     *      - the difference in x-axis between 0 and X is 2
     *      - the difference in y-axis between 0 and X is 1
     * 
     * And note that in the output map:
     *      - the difference in x-axis between 0 and X is 1
     *      - the difference in y-axis between 0 and X is 2
     * 
     * So we understand that the 2 distances must be swapped.
     * However we have also to notice that if 0 is more to the right than X,
     * its y coordinate will decrease (which means that 0 will go up).
     * The same thought can be applyed to x coordinate (if 0 is upper than X, ...)
     */

}

void rotateCShip(Ship *ship, Coordinate center)
{
    int cursor;
    int tempX;
    

    for ( cursor = 0; cursor < ship -> length; cursor++ )
    {
        tempX = ship -> points[cursor].x;
        ship -> points[cursor].x = center.x + (center.y - ship -> points[cursor].y);
        ship -> points[cursor].y = center.y + (tempX - center.x);

    }

    /* To understand what this 2 lines of code do, look at the comment in 
     * rotateAntiC and be aware of the fact that this code does exactly the opposite.
     */

}
