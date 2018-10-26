/*************************************************************
* File: flyingObject.h
* Author: Matthew Burr
*
* Description: Contains the definition of a Flying Object - an
*  object that moves across the screen with a defined velocity
*************************************************************/
#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"

/*****************************************
* FLYING OBJECT
* A class from which all flying objects
* derive and that defines how flying
* objects move across the screen
*****************************************/
class FlyingObject
{
private:
   Point m_point;
   Velocity m_velocity;
   bool m_isAlive;
   static bool s_hasBoundaries;
   static Point s_topLeft;
   static Point s_bottomRight;   

   static Point getTopLeft() { return s_topLeft; }
   static Point getBottomRight() { return s_bottomRight; }

public:
   static void setBoundaries(const Point &in_tl, const Point &in_br);
   FlyingObject();

   Point getPoint() const;
   Velocity getVelocity() const;
   virtual float getRadius() const { return 0; }
   void setPoint(const Point &in_point);
   void setVelocity(const Velocity &in_velocity);
   bool isAlive() const;
   virtual void kill();
   virtual void advance();
   virtual void draw() const = 0;
   FlyingObject & operator+=(const Velocity & rhs);
};

#endif /* flyingObject_h */
