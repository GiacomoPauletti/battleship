#include "rotation.h"


void rotateAntiC(Coordinate *points, int length, Coordinate center)
{
    int cursor;
    int tempX;
    

    for ( cursor = 0; cursor < length; cursor++ )
    {
        tempX = points[cursor].x;
        points[cursor].x = center.x + (points[cursor].y - center.y);
        points[cursor].y = center.y + (center.x - tempX);

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

void rotateC(Coordinate *points, int length, Coordinate center)
{
    int cursor;
    int tempX;
    

    for ( cursor = 0; cursor < length; cursor++ )
    {
        tempX = points[cursor].x;
        points[cursor].x = center.x + (center.y - points[cursor].y);
        points[cursor].y = center.y + (tempX - center.x);

    }

    /* To understand what this 2 lines of code do, look at the comment in 
     * rotateAntiC and be aware of the fact that this code does exactly the opposite.
     */

}
