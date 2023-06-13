/***********************************************************************
 * Header File:
 *    Moon Lander : Takes care of the fuel and physics of the moon lander's
 *    movement
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once

#include "point.h"
#include "trigonometry.h"
#include "physics.h"
 /*********************************************
  * MOON LANDER
  * our lunar module that player must land
  *********************************************/
class MoonLander
{
public:
    MoonLander(Point location);
    double getAngle() { return angle; }
    Point getLocation() { return location; }
    void setAngle(double angle) { this->angle = angle; }
    void addAngle(double ammount) { angle += ammount; }
    bool getLeftThruster() { return (leftThrusterActive && alive && (fuel > 0.0)); }
    bool getRightThruster() { return (rightThrusterActive && alive && (fuel > 0.0)); }
    bool getDownThruster() { return (downThrusterActive && alive && (fuel > 0.0)); }
    void setLeftThruster(bool state) { leftThrusterActive = state && alive && (fuel > 0.0); }
    void setRightThruster(bool state) { rightThrusterActive = state && alive && (fuel > 0.0); }
    void setDownThruster(bool state) { downThrusterActive = state && alive && (fuel > 0.0); }
    void move();
    double getVelocity() { return physics.get_velocity(); }
    bool isAlive() { return alive; }
    bool isLanded() { return landed; }
    double getFuel() { return fuel; }
    int getWidth() { return width; }
    
    void die();
    void land();

private:
    Physics physics;
    double angle;
    Point location;
    bool leftThrusterActive;
    bool rightThrusterActive;
    bool downThrusterActive;
    double fuel;                // Fuel is in Kilograms! Kg is used to easily calculate the physics
    double landerMass;          // In Kilograms
    double thrusterForce;       // In Newtons
    bool alive;
    bool landed;
    int width = 20;

    void burnFuel(double ammount);
};
