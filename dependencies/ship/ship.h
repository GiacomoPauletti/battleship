#include "../map/map.h"

#define MAX_SHIP_NUM 20
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

typedef struct
{
    Ship ships[MAX_SHIP_NUM];
    int shipNum;

} Army;

int initDefaultArmy(Army *defaultArmy);
/* initDefaultArmy
 * This function initializes the default ship army used during the game
 *
 * Returns 1 if success, 0 if error
 */

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

int isPlaceable(MapWrap map, Ship ship);
/* isPlaceable
 * this function checks whether a ship is placeable in the passed map
 * If it is placeable, 1 will be returned.
 * If it is not placeable, 0 will be returned.
 */

int placeShip(MapWrap *map, Ship ship);
/* placeShip
 * First checks whether a ship is placeable by calling isPlaceable.
 * If the ship is placeable, it places it.
 *
 * Returns 1 if success, 0 if error
 */

int unplaceShip(MapWrap *map, Ship ship);
/* unplaceShip
 * Remove given ship from given map
 *
 * Returns 1 if success, 0 if error
 */

int moveShip(Ship *ship, int deltaX, int deltaY);
/* moveShip
 * translate ship on x-axis and y-axis respectively of deltaX and deltaY
 *
 * Returns 1 if success, 0 if error
 */

int checkMovValidity(MapWrap map, Ship ship, int deltaX, int deltaY);
/* checkMovValidity
 * checks whether moving the ship is valid.
 * Movement is not valid if ship moves outside map borders.
 * 
 * Returns 1 if movement is valid, 0 if not.
 */

int checkACRotValidity(MapWrap map, Ship ship, Coordinate center);
/* checkACRotValidity
 * checks whether rotating anti-clockwise the ship is valid.
 * Rotation is not valid if ship points would get placed outside map borders.
 * 
 * Returns 1 if rotation is valid, 0 if not.
 */

int checkCRotValidity(MapWrap map, Ship ship, Coordinate center);
/* checkCRotValidity
 * checks whether rotating clockwise the ship is valid.
 * Rotation is not valid if ship points would get placed outside map borders.
 * 
 * Returns 1 if rotation is valid, 0 if not.
 */

void rotateACShip(Ship *ship, Coordinate center);
/* rotateAntiC
 * rotates anti-clockwise around the center the given ship.
 */

void rotateCShip(Ship *ship, Coordinate center);
/* rotateC
 * rotates clockwise around the center the given ship
 */
#endif