#include <stdio.h>
#include "../map/map.h"

#if !defined(ROTATION_H)
#define ROTATION_H


void rotateAntiC(Coordinate *points, int length, Coordinate center);
/* rotateAntiC
 * rotates anti-clockwise around the center the group of points passed.
 */

void rotateC(Coordinate *points, int length, Coordinate center);
/* rotateC
 * rotates clockwise around the center the group of points passed.
 */

#endif