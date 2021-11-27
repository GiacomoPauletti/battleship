#include "ship.h"

int isLegal(Ship ship)
{
    Ship checkedShip;
    checkedShip.points[0] = ship.points[0];
    checkedShip.length = 1;
    
    return 1;
}

Ship findShip(Map map, Coordinate point, Ship ship)
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

        if ( ( newPoint.x > 0 && newPoint.x < MAP_WIDTH ) && ( newPoint.y >= 0 && newPoint.y < MAP_HEIGHT ) )
        /* not accepting points that are not in the map range */
        {

            if ( map[newPoint.y][newPoint.x] == SAFE_SHIP_CHAR )
            {
                isNewPoint = 1;
                for (pointCursor = 0; pointCursor < ship.length && isNewPoint == 1; pointCursor++)
                {
                    if ( ( ship.points[pointCursor].x == newPoint.x ) &&
                        ( ship.points[pointCursor].y == newPoint.y ) )
                        isNewPoint = 0;
                }

                if ( isNewPoint == 1 )
                {
                    ship.points[ship.length] = newPoint;
                    ship.length++;

                    findShip(map, newPoint, ship);
                }
            }

        }

    }

    return ship;

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
        else if ( map[ship.points[cursor].y][ship.points[cursor].x] != EMPTY_CHAR )
            /* if the point is overlapping with an already filled point, 0 will be returned */
            isPlaceable = 0;

    }
    /* if every point is placeable, 1 will be returned */
    return isPlaceable;
}

/*
int placeShip(Map map, Ship ship)
{
    int cursor;
    int validPosition;
    int shipX, shipY;
     
    if ( isPlaceable(map, ship) == 1)
    {
        for ( cursor = 0; cursor < ship.length; cursor++ )
        {
            shipX = ship.points[cursor].x;
            shipY = ship.points[cursor].y;

            if (map[shipY][shipX] != EMPTY_CHAR)
        }
    }


}*/

