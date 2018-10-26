/*************************************************************
* File: velocity.cpp
* Author: Matthew Burr
*
* Description: Implements the Velocity class
*************************************************************/

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include "velocity.h"

/**********************************************************************
 * Method: FromAngularSpeed
 * Description: Converts an angle and speed into a Velocity
 **********************************************************************/
Velocity Velocity::FromAngularSpeed(float angle, float speed)
{
   float dx = speed * (cos(M_PI / 180.0 * angle));
   float dy = speed * (sin(M_PI / 180.0 * angle));
   
   return Velocity(dx, dy);
}

/**********************************************************************
* Method: Velocity
* Description: Creates a new Velocity with default values
**********************************************************************/
Velocity::Velocity()
{
   setDx(0);
   setDy(0);
}

/**********************************************************************
* Method: Velocity
* Description: Creates a new Velocity with specified values
**********************************************************************/
Velocity::Velocity(float dx, float dy)
{
   setDx(dx);
   setDy(dy);
}

/**********************************************************************
* Method: setDx
* Description: Changes the lateral Velocity
**********************************************************************/
void Velocity::setDx(float dx)
{
   m_dX = dx;
}

/**********************************************************************
* Method: getDx
* Description: Gets the lateral Velocity
**********************************************************************/
float Velocity::getDx() const
{
   return m_dX;
}

/**********************************************************************
* Method: setDy
* Description: Sets the vertical Velocity
**********************************************************************/
void Velocity::setDy(float dy)
{
   m_dY = dy;
}

/**********************************************************************
* Method: getDy
* Description: Gets the vertical Velocity
**********************************************************************/
float Velocity::getDy() const
{
   return m_dY;
}

/**********************************************************************
 * Method: addVelocity
 * Description: Adds an input velocity to this one
 **********************************************************************/
void Velocity::addVelocity(const Velocity &in_velocity)
{
   m_dX += in_velocity.m_dX;
   m_dY += in_velocity.m_dY;
}

/**********************************************************************
* Operator: +=
* Description: Adds on to a velocity
**********************************************************************/
Velocity & Velocity::operator+=(const Velocity & rhs)
{
   this->m_dX += rhs.m_dX;
   this->m_dY += rhs.m_dY;
   return *this;
}

/**********************************************************************
* Operator: +
* Description: Adds together two velocities
**********************************************************************/
 Velocity operator+(const Velocity & lhs, const Velocity & rhs)
 {
    return Velocity(lhs.m_dX + rhs.m_dX, lhs.m_dY + rhs.m_dY);
 }
