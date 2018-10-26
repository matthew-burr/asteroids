/*************************************************************
* File: rocks.cpp
* Author: Matthew Burr
*
* Description: Contains the implementations of the
*  method bodies for the Rock classes.
*************************************************************/
#include "rocks.h"
#include "point.h"
#include "uiDraw.h"
#include "velocity.h"
#include <list>

#define MAX_DEGREES 360
using namespace std;

/**********************************************************************
* ROCK CLASS IMPLEMENTATION
***********************************************************************/

/**********************************************************************
* Method: Rock
* Description: Creates a new instance of Rock
**********************************************************************/
Rock::Rock() : m_rotation(0)
{
}

Rock::Rock(const Point &in_point, float in_angle) : m_rotation(0)
{
   launch(in_point, in_angle);
}

Rock::Rock(const Point & in_point, float dx, float dy) : m_rotation(0)
{
   launch(in_point, dx, dy);
}

/**********************************************************************
 * Method: launch
 * Description: Launches a rock from a given in_point in a given direction
 *  with a constant in_speed
 **********************************************************************/
void Rock::launch(const Point &in_point, float in_angle)
{
   setPoint(in_point);
   setVelocity(Velocity::FromAngularSpeed(in_angle, DEFAULT_ROCK_SPEED));
}

/**********************************************************************
* Method: launch
* Description: Launches a rock from a given in_point in a given direction
*  with a particular velocity in the x and y axes
**********************************************************************/
void Rock::launch(const Point &in_point, float dx, float dy)
{
   setPoint(in_point);
   setVelocity(Velocity(dx, dy));
}

/**********************************************************************
 * Method: HIT
 * Description: Hits the rock, potentially turning it into a set
 * of fragments.
 **********************************************************************/
 std::list<Rock*>* Rock::hit()
 {
    kill();
    return getFragments();
 }

/**********************************************************************
 * Method: advance
 * Description: Moves the rock and changes its rotation
 **********************************************************************/
void Rock::advance()
{
   FlyingObject::advance();
   m_rotation = (m_rotation + getSpin()) % MAX_DEGREES;
}

/**********************************************************************
 * BIG ROCK CLASS IMPLEMENTATION
 **********************************************************************/
/**********************************************************************
 * Method: getFragments
 * Description: Gets the fragments from this rock
 **********************************************************************/
std::list<Rock*>* BigRock::getFragments()
{
   float dx = getVelocity().getDx();
   float dy = getVelocity().getDy();
   list<Rock*> * fragments = new list<Rock*>;

   fragments->push_back(new MediumRock(getPoint(), dx, dy + 1));
   fragments->push_back(new MediumRock(getPoint(), dx, dy - 1));
   fragments->push_back(new SmallRock(getPoint(), dx + 2, dy));

   return fragments;
}

/**********************************************************************
 * Method: draw
 * Description: Draws the BigRock on the screen
 **********************************************************************/
void BigRock::draw() const
{
   drawLargeAsteroid(getPoint(), getRotation());
}

/**********************************************************************
* MEDIUM ROCK CLASS IMPLEMENTATION
**********************************************************************/
/**********************************************************************
 * Method: getFragments
 * Description: Gets the fragments from this rock
 **********************************************************************/
std::list<Rock*>* MediumRock::getFragments()
{
   float dx = getVelocity().getDx();
   float dy = getVelocity().getDy();
   list<Rock*> * fragments = new list<Rock*>;

   fragments->push_back(new SmallRock(getPoint(), dx + 3, dy));
   fragments->push_back(new SmallRock(getPoint(), dx - 3, dy));

   return fragments;
}

/**********************************************************************
 * Method: draw
 * Description: Draws the rock on the screen
 **********************************************************************/
void MediumRock::draw() const
{
   drawMediumAsteroid(getPoint(), getRotation());
}

/**********************************************************************
* SMALL ROCK CLASS IMPLEMENTATION
**********************************************************************/
/**********************************************************************
* Method: getFragments
* Description: Gets the fragments from this rock
**********************************************************************/
std::list<Rock*>* SmallRock::getFragments()
{
   return new std::list<Rock*> ;
}

/**********************************************************************
* Method: draw
* Description: Draws the rock on the screen
**********************************************************************/
void SmallRock::draw() const
{
   drawSmallAsteroid(getPoint(), getRotation());
}