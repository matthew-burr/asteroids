/*************************************************************
* File: bullet.h
* Author: Matthew Burr
*
* Description: Contains the definition of a Bullet class: a
*  projectile that travles in a straight line and can kill a
*  bird
*************************************************************/

#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"


/*****************************************
* BULLET
* A projectile that can be fired
*****************************************/
class Bullet :
   public FlyingObject
{
private:
   int m_life;

public:
   Bullet();
   virtual float getRadius() const { return 5; }
   void fire(const Point &in_point, float in_angle);
   virtual void advance();
   void draw() const;
};

#endif // !BULLET_H

