/***********************************************************************
* Header File:
*    Velocity : The representation of a the Velocity of a Moon Lander
* Author:
*    Matthew Burr
* Summary:
*    Everything to represent the Velocity of a Moon Lander (or anything
*    else that moves in 2D space)
************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
   float m_dX;
   float m_dY;

public:
   static Velocity FromAngularSpeed(float angle, float speed);
   
   Velocity();
   Velocity(float dx, float dy);

   float getDx() const;
   float getDy() const;
   void setDx(float dx);
   void setDy(float dy);
   void addVelocity(const Velocity &in_velocity);

   Velocity & operator+=(const Velocity &rhs);
   friend Velocity operator+(const Velocity &lhs, const Velocity &rhs);
};

#endif /* velocity_h */
