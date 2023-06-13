/***********************************************************************
 * Header File:
 *    Moon Lander : Takes care of the fuel and physics of the moon lander's
 *    movement
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#include "moonlander.h"
#include "point.h"

 /******************************************
  * POINT : CONSTRUCTOR WITH X,Y
  * Initialize the point to the passed position
  *****************************************/
MoonLander::MoonLander(Point location) {
    physics = Physics();
    this->location = location;
    angle = 0.0;
    leftThrusterActive = false;
    rightThrusterActive = false;
    downThrusterActive = false;
    fuel = 2268.0;
    landerMass = 12835.0;
    thrusterForce = 45000.0;
    alive = true;
    landed = false;
}


/******************************************
  * POINT : CONSTRUCTOR WITH X,Y
  * Initialize the point to the passed position
  *****************************************/
void MoonLander::move()
{
    if (alive && !landed) {

        if (fuel > 0) {
            if (leftThrusterActive) {
                addAngle(0.1);
                //dx = dx - 0.05;
                burnFuel(0.45);
            }
            if (rightThrusterActive) {
                addAngle(-0.1);
                //dx = dx + 0.05;
                burnFuel(0.45);
            }
            if (downThrusterActive) {
                burnFuel(4.5);
            }
        }

        physics.compute_physics(thrusterForce * (int)downThrusterActive, landerMass + fuel, angle);
        location = physics.compute_location(location);

    }
}

/******************************************
  * POINT : CONSTRUCTOR WITH X,Y
  * Initialize the point to the passed position
  *****************************************/
void MoonLander::die()
{
    alive = false;
    angle = 3.2;
    leftThrusterActive = false;
    rightThrusterActive = false;
    downThrusterActive = false;
}

void MoonLander::land()
{
    landed = true;
    leftThrusterActive = false;
    rightThrusterActive = false;
    downThrusterActive = false;
}

void MoonLander::burnFuel(double ammount)
{
    fuel = fuel - ammount;
    if (fuel < 0.0)
        fuel = 0.0;
}
