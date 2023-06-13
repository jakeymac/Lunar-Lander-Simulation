#pragma once

#include <cmath>

using namespace std;

class Trigonometry {
public:
	static double computeVerticalComponent(double radians, double total) { return total * cos(radians); }
	static double computeHorizontalComponent(double radians, double total) { return total * sin(radians); }
	static double computeTotalComponent(double horizontalComponent, double verticalComponent) { return sqrt(pow(horizontalComponent, 2) + pow(verticalComponent, 2)); }
};