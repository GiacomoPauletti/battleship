#include "../map/map.h"

#define DEFAULT_SHIP_NUM 10
#define MAX_SHIP_POINTS 6


#if !defined(SHIP_H)
#define SHIP_H

extern int SHIP_NUMBER;

typedef struct 
{
    Coordinate points[MAX_SHIP_POINTS];
    int length; 
    int hitCounter;
    
} Ship;

int isLegal(Ship ship);
/* isLegal
 * This function checks whether the given ship is legal.
 * A ship is considered legal if all points are adiacent to at least another point 
 * and all points are part of an unique ship (ship made of multiple parts are not admitted)
 * Two points are adiacent if they are placed in two contiguous cells (horizontally and
 * vertically but not diagonally)
 * 
 * EXAMPLES:
 * 
 *      OOO         O  O
 *     O  O         O  O
 * 
 * These two ships are illegal:
 *  -first ship has one point (bottom-left one) which is not adiacent 
 *  -second ship has all adiacent points but they do not form a unique ship
 * 
 *      OOO         OOOO
 *      O           O  O
 * 
 * These are the corrected versions of ships of the previous example.
 * (Note that even though it does not seem so, they are also vertically adiacent)
 */

int isPlaceable(Map map, Ship ship);
/* isPlaceable
 * this function checks whether a ship is placeable in the passed map
 * If it is placeable, 1 will be returned.
 * If it is not placeable, 0 will be returned.
 */

int placeShip(Map map, Ship ship);
/* isPlaceable
 * First checks whether a ship is placeable by calling isPlaceable.
 * If the ship is placeable, it places it.
 */

#endif