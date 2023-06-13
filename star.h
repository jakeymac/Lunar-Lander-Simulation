/***********************************************************************
 * Header File:
 *    STAR : just a little star for the background
 *
 * Author:
 *    Jaden Myers
 * Summary:
 *    star for background image of the screen
 ************************************************************************/

#pragma once

#include "point.h"

class Star
{
public:
    Star();
    Star(Point pt);
    void phaseShift() { phase++; }
    Point getPoint() { return pt; }
    unsigned char getPhase() { return phase; }

private:
    Point pt;
    unsigned char phase;
};