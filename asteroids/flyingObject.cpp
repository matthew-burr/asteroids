/*************************************************************
* File: flyingObject.cpp
* Author: Matthew Burr
*
* Description: Contains the implementations of the
*  method bodies for the flyingObject class.
*************************************************************/

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"

bool FlyingObject::s_hasBoundaries(false);
Point FlyingObject::s_topLeft(0, 0);
Point FlyingObject::s_bottomRight(0, 0);

/**********************************************************************
 * Method: setBoundaries
 * Description: Sets the boundaries for all FlyingObjects. They will
 * stay within these boundaries - wrapping around to the other side
 * if they reach one of the bounds.
 **********************************************************************/
void FlyingObject::setBoundaries(const Point &in_tl, const Point &in_br)
{
   s_topLeft = in_tl;
   s_bottomRight = in_br;
   s_hasBoundaries = true;
}

/**********************************************************************
* Method: FlyingObject
* Description: Creates a new FlyingObject
**********************************************************************/
FlyingObject::FlyingObject() : m_isAlive(true)
{
}

/**********************************************************************
* Method: getPoint
* Description: Gets the point (location) of the object
**********************************************************************/
Point FlyingObject::getPoint() const
{
   return m_point;
}

/**********************************************************************
* Method: getVelocity
* Description: Gets the velocity for the object
**********************************************************************/
Velocity FlyingObject::getVelocity() const
{
   return m_velocity;
}

/**********************************************************************
* Method: isAlive
* Description: True if the object is alive; false otherwise
**********************************************************************/
bool FlyingObject::isAlive() const
{
   return m_isAlive;
}

/**********************************************************************
* Method: setPoint
* Description: Sets the point (location) of the object
**********************************************************************/
void FlyingObject::setPoint(const Point &in_point)
{
   m_point = in_point;
}

/**********************************************************************
* Method: setVelocity
* Description: Sets the velocity for the object
**********************************************************************/
void FlyingObject::setVelocity(const Velocity &in_velocity)
{
   m_velocity = in_velocity;
}

/**********************************************************************
* Method: kill
* Description: Kills the object so it is no longer alive
**********************************************************************/
void FlyingObject::kill()
{
   m_isAlive = false;
}

/**********************************************************************
* Method: advance
* Description: Moves the object to a new location according to its
*              velocity
**********************************************************************/
void FlyingObject::advance()
{
   m_point += m_velocity;

   // If we have boundaries, then we need to keep the point within 
   // the bounds of s_topLeft &
   // s_bottomRight. 
   if (!s_hasBoundaries)
      return;

   if (m_point.getX() < s_topLeft.getX())
   {
      m_point.setX(s_bottomRight.getX());
   }
   else if (m_point.getX() > s_bottomRight.getX())
   {
      m_point.setX(s_topLeft.getX());
   }

   if (m_point.getY() < s_bottomRight.getY())
   {
      m_point.setY(s_topLeft.getY());
   }
   else if (m_point.getY() > s_topLeft.getY())
   {
      m_point.setY(s_bottomRight.getY());
   }
}

/**********************************************************************
* Method: operator+=
* Description: Applies a velocity to a flying object, essentially
* increasing its velocity
**********************************************************************/
FlyingObject & FlyingObject::operator+=(const Velocity & rhs)
{
   m_velocity += rhs;
   return *this;
}
