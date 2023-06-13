#pragma once
#include "point.h"
#include "trigonometry.h"

class Physics {
public:
    Physics()
    {
        t = 1.0 / 10.0;
        gravity = 1.625;
        dv = 0.0;
        ddx = 0.0;
        ddy = 0.0;
        v = 0.0;
        dx = -1.0;
        dy = 0.0;
    }

    void compute_physics(double force, double mass, double radians) 
    { 
        compute_acceleration(force, mass, radians);
        compute_velocity();
    }

    double getGravity() { return gravity * t; }
    void applyGravity() { dy = dy - getGravity(); }

    void compute_acceleration(double force, double mass, double radians) 
    {
        dv = force / mass;
        ddx = Trigonometry::computeHorizontalComponent(radians, dv);
        ddy = Trigonometry::computeVerticalComponent(radians, dv);
    }

    void compute_velocity() 
    {
        dx = dx - (ddx * t);
        dy = dy + (ddy * t);

        applyGravity();

        v = Trigonometry::computeTotalComponent(dx, dy);
    }

    Point compute_location(Point pt)
    {
        pt.addX(dx * t);
        pt.addY(dy * t);
        return pt;
    }

    double get_velocity() { return v; }

private:
    double t;
    double gravity;
    double dv;          // Delta Velocity a.k.a. Total Acceleration
    double ddx;         // Horizontal Acceleration
    double ddy;         // Vertical Acceleration
    double v;           // Total Velocity
    double dx;          // Horizontal Velocity
    double dy;          // Vertical Velocity
};
