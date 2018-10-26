/*************************************************************
* File: ship.h
* Author: Matthew Burr
*
* Description: Contains the declaration of a Ship class
*************************************************************/

#ifndef ship_h
#define ship_h

#include "flyingObject.h"
#include "bullet.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

/*****************************************
* SHIP
* A class representing a spacecraft that
* can rotate and move under user control
* and can fire bullets.
*****************************************/
class Ship : public FlyingObject
{
public:
   Ship();
   virtual float getRadius() const { return SHIP_SIZE; }
   virtual void advance();
   virtual void draw() const;
   void rotateRight();
   void rotateLeft();
   void thrust();
   virtual void kill();
   void setInvulnerable(int in_timer);
   Bullet fire() const;

private:
   int m_rotation;
   int m_invulnerableTimer;
   bool m_thrusted;
   bool m_drawThrust;
   bool m_isInvulnerable;
};



#endif /* ship_h */
