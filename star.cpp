/***********************************************************************
 * Header File:
 *    STAR : just a little star for the background
 *
 * Author:
 *    Jaden Myers
 * Summary:
 *    star for background image of the screen
 ************************************************************************/

#include "star.h"
#include "point.h"
#include "uiDraw.h"

 /******************************************
   * POINT : CONSTRUCTOR WITH X,Y
   * Initialize the point to the passed position
   *****************************************/
Star::Star(Point pt)
{
    this->pt = pt;
    phase = random(0, 255);
}

/******************************************
   * POINT : CONSTRUCTOR WITH X,Y
   * Initialize the point to the passed position
   *****************************************/
Star::Star()
{
    pt = Point();
    phase = random(0, 255);
}