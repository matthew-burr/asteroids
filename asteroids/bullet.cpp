/*************************************************************
* File: bullet.cpp
* Author: Matthew Burr
*
* Description: Contains the implementations of the
*  method bodies for the bullet class.
*************************************************************/

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include "bullet.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "flyingObject.h"
#include <cmath>

#define HALF_CIRCLE 180.0

/**********************************************************************
* Method: Bullet
* Description: Creates a new Bullet
**********************************************************************/
Bullet::Bullet()
   : m_life(BULLET_LIFE)
{
}

/**********************************************************************
* Method: fire
* Description: Fires a bullet in a straight line in a specific
*              direction
**********************************************************************/
void Bullet::fire(const Point &in_point, float in_angle)
{
   setPoint(in_point);
   setVelocity(Velocity::FromAngularSpeed(in_angle, BULLET_SPEED));
}

/**********************************************************************
* Method: Advance
* Description: Moves the bullet forward. Kills it if it's been around
* too long.
**********************************************************************/
void Bullet::advance()
{
   FlyingObject::advance();
   
   if (m_life > 0)
      if (--m_life <= 0)
         kill();
}

/**********************************************************************
* Method: draw
* Description: Draws the bullet on the screen
**********************************************************************/
void Bullet::draw() const
{
   drawDot(getPoint());
}