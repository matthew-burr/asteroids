/*************************************************************
* File: ship.cpp
* Author: Matthew Burr
*
* Description: Contains the implementations of the
*  method bodies for the Ship class.
*************************************************************/
#include "ship.h"
#include "uiDraw.h"
#include "bullet.h"
#include "flyingObject.h"
#include <cassert>

#define ROTATION_DRAW_OFFSET 90
#define STARTING_ROTATION ROTATION_DRAW_OFFSET
#define MAX_DEGREES 360
#define BLINK_PACE 10
#define BLINK_LIMIT (BLINK_PACE / 2)

/**********************************************************************
 * Method: Ship
 * Description: Creates a new Ship
 **********************************************************************/
Ship::Ship() 
   : m_rotation(STARTING_ROTATION), m_thrusted(false), m_drawThrust(false),
   m_isInvulnerable(false), m_invulnerableTimer(0)
{
}

/**********************************************************************
* Method: ADVANCE
* Description: Moves the ship and determines whether to draw thrust
* or not.
**********************************************************************/
void Ship::advance()
{
   FlyingObject::advance();

   // We countdown on the invulnerability timer if the ship is 
   // invulnerable
   if (m_isInvulnerable)
   {
      m_invulnerableTimer--;

      // We turn off invulnerability and set the time to 0
      // if the timer has expired
      if (m_invulnerableTimer <= 0)
         m_isInvulnerable = m_invulnerableTimer = 0;
   }

   // We need a way to indicate to the draw method whether it should
   // draw thrust or not, so we check to see if the user pressed
   // thrust recently
   if (m_thrusted)
   {
      // If they did, we'll draw thrust on the next draw
      // and reset our m_thrusted to false
      m_drawThrust = true;
      m_thrusted = false;
   }
   else
   {
      // Otherwise, we don't draw thrust
      m_drawThrust = false;
   }
}

/**********************************************************************
 * Method: draw
 * Description: Draws a ship on the screen
 **********************************************************************/
void Ship::draw() const
{
   // As an indicator of invulnerability, we "flash" the ship
   // on and off while it's invulnerable
   if (m_isInvulnerable)
   {
      // If it's invulnerable, we draw it every other frame
      // using the timer as a convenient way to determine
      // whether to draw it this frame or not
      if (m_invulnerableTimer % BLINK_PACE < BLINK_LIMIT)
         drawShip(getPoint(), m_rotation - ROTATION_DRAW_OFFSET, m_drawThrust);
   }
   else
   {
      drawShip(getPoint(), m_rotation - ROTATION_DRAW_OFFSET, m_drawThrust);
   }
}

/**********************************************************************
 * Method: rotateRight
 * Description: Rotates the ship clockwise
 **********************************************************************/
void Ship::rotateRight()
{
   m_rotation = (m_rotation - ROTATE_AMOUNT) % MAX_DEGREES;
}

/**********************************************************************
 * Method: rotateLeft
 * Description: Rotates the ship counter-clockwise
 **********************************************************************/
void Ship::rotateLeft()
{
   m_rotation = (m_rotation + ROTATE_AMOUNT) % MAX_DEGREES;
}

/**********************************************************************
 * Method: thrust
 * Description: Adds force in the direction the Ship currently faces
 **********************************************************************/
void Ship::thrust()
{
   *this += Velocity::FromAngularSpeed(m_rotation, THRUST_AMOUNT);
   m_thrusted = true;
}


/**********************************************************************
* Method: kill
* Description: If the ship is not invulnerable, kill it
**********************************************************************/
void Ship::kill()
{
   if (m_isInvulnerable)
      return;

   FlyingObject::kill();
}

/**********************************************************************
* Method: setInvulnerable
* Description: Makes the ship invulnerable for a limited amount of time
**********************************************************************/
void Ship::setInvulnerable(int in_timer)
{
   assert(in_timer >= 0);
   if (in_timer < 0)
      in_timer = 0;

   m_isInvulnerable = m_invulnerableTimer = in_timer;
}

/**********************************************************************
 * Method: fire
 * Description: Fires a Bullet
 **********************************************************************/
Bullet Ship::fire() const
{
   Bullet b;
   b.fire(getPoint(), m_rotation);
   b += getVelocity();
   return b;
}