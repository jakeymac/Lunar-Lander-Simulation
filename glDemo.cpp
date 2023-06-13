/**********************************************************************
 * GL Demo
 * Just a simple program to demonstrate how to create an Open GL window,
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "moonlander.h"
#include "star.h"
using namespace std;

//Testing testing
/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(const Point& ptUpperRight) :
        ground(ptUpperRight),
        moonLander(Point(ptUpperRight.getX() - 50.0, ptUpperRight.getY() - 50.0))

    {
        this->ptUpperRight = ptUpperRight;

        for (int count = 0; count < 50; count++) {
            double x = random(0.0, ptUpperRight.getX());
            double y = random(ground.getY(x), ptUpperRight.getY());
            stars[count] = Star(Point(x, y));
        }
    }

    // this is just for test purposes.  Don't make member variables public!
    Point ptUpperRight;   // size of the screen
    MoonLander moonLander;
    Ground ground;
    Star stars[50];
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    ogstream gout;
    
    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL.
    Demo* pDemo = (Demo*)p;
    
    // move the ship around
    if (pDemo ->ground.onPlatform(pDemo->moonLander.getLocation(), pDemo->moonLander.getWidth())) {
        if(pDemo->moonLander.getVelocity() < 4.0) {
            //Moon lander landed method
            pDemo->moonLander.land();
        } else {
            pDemo->moonLander.die();
        }
    }
    else if (pDemo->ground.hitGround(pDemo->moonLander.getLocation(), pDemo->moonLander.getWidth())) {
        pDemo->moonLander.die();
    }
    
    
    
    if (pDemo->moonLander.isLanded()) {
        //Display winning message 'eagle is landed'
        gout.setPosition(Point(110,290));
        gout << "The eagle has landed";
    }

    else if (!pDemo->moonLander.isAlive()) {
        //Display losing message 'Houston, we have a problem'
        gout.setPosition(Point(100,290));
        gout << "Houston, we have a problem";
    }

    pDemo->moonLander.setRightThruster(pUI->isRight());
    pDemo->moonLander.setLeftThruster(pUI->isLeft());    
    pDemo->moonLander.setDownThruster(pUI->isDown());
    pDemo->moonLander.move();

    // draw the ground
    pDemo->ground.draw(gout);

    // draw the lander and its flames
    gout.drawLander(pDemo->moonLander.getLocation() /*position*/, pDemo->moonLander.getAngle() /*angle*/);
    gout.drawLanderFlames(pDemo->moonLander.getLocation(), pDemo->moonLander.getAngle(), /*angle*/
    pDemo->moonLander.getDownThruster(), pDemo->moonLander.getLeftThruster(), pDemo->moonLander.getRightThruster());

    // put some text on the screen
    gout.setf(ios::fixed);
    gout.setf(ios::showpoint);
    gout.precision(2);

    double leftMargin = 15.0;
    double topOfScreen = pDemo->ptUpperRight.getY();
    double lineSpace = 20.0;

    double fuel = pDemo->moonLander.getFuel() * 2.205;      // the moonlander returns kg and multiplying by 2.205 converts it to lbs
    double altitude = pDemo->ground.getElevation(pDemo->moonLander.getLocation());
    double speed = pDemo->moonLander.getVelocity();

    gout.setPosition(Point(leftMargin, topOfScreen - lineSpace * 1));
    gout << "Fuel:     " << (int)fuel << " lbs\n";

    gout.setPosition(Point(leftMargin, topOfScreen - lineSpace * 2));
    gout << "Altitude: " << (int)altitude << " meters\n";

    gout.setPosition(Point(leftMargin, topOfScreen - lineSpace * 3));
    gout << "Speed:   " << speed << " m/s\n";

    // draw our little stars
    for (Star& star : pDemo->stars) {
        gout.drawStar(star.getPoint(), star.getPhase());
        star.phaseShift();
    }
    
    float sunX = 325.0;
    float sunY = 375.0;
    gout.drawSun(Point(sunX,sunY));
    
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main()
#endif // !_WIN32
{
    // Initialize OpenGL
    Point ptUpperRight(400.0, 400.0);
    Interface ui(0, NULL,
        "Open GL Demo",
        ptUpperRight);

    // Initialize the game class
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);

    return 0;
}
