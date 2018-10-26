/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/
 // Turn this on for testing purposes to make the ship invincible
 //#define INVINCIBLE

#include "game.h"
#include "uiInteract.h"
#include "point.h"
#include "uiDraw.h"
#include "flyingObject.h"
#include <cassert>
#include <sstream>
// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include <vector>
#include <list>

#define MISS 0
#define HIT 1
#define SCORE_X_OFFSET 5
#define SCORE_Y_OFFSET -20
#define LIVES_X_OFFSET SCORE_X_OFFSET
#define LIVES_Y_OFFSET (SCORE_Y_OFFSET - 20)
#define MAX_LIVES 3
#define DEFAULT_INVULNERBILITY_TIME 100
#define START_ROCK_COUNT 5
#define MIN_ANGLE 0
#define MAX_ANGLE 360
using namespace std;

/**********************************************************************
 * Method: Game
 * Description: Creates a new instance of Game
 **********************************************************************/
Game::Game(Point tl, Point br)
   : m_topLeft(tl), m_bottomRight(br), m_lives(MAX_LIVES)
{
   FlyingObject::setBoundaries(tl, br);
   m_score = 0;
   
   initializeRocks();

   // Just in case there's a rock in the nearby vicinity
   // the ship is temporarily invulnerable
   m_ship.setInvulnerable(DEFAULT_INVULNERBILITY_TIME);
}

/**********************************************************************
 * Method: ~Game
 * Description: Cleans up a destroyed Game instance
 **********************************************************************/
Game::~Game()
{
   // Delete all rock pointers
   for (list<Rock*>::iterator it = m_rocks.begin();
      it != m_rocks.end(); ++it)
   {
      delete *it;
      *it = NULL;
   }
}

/**********************************************************************
 * Method: advance
 * Description: Advances objects in the Game by one frame of action.
 **********************************************************************/
void Game::advance()
{
   advanceRocks();

   advanceBullets();

   // If the ship is alive, we advance it.
   // If it's dead, we see if we should revive it (i.e. if
   // we haven't heard our limit on deaths, we'll create it
   // anew
   if (m_ship.isAlive())
      m_ship.advance();
   else
   {
      if (m_lives > 0)
      {
         m_ship = Ship();
         m_ship.setInvulnerable(DEFAULT_INVULNERBILITY_TIME);
      }
   }

   handleCollisions();

   cleanupZombies();
}

/**********************************************************************
* Method: cleanupZombies
* Description: Cleans up all the dead stuff
**********************************************************************/
void Game::cleanupZombies()
{
   cleanupBullets();
   cleanupRocks();
}

/**********************************************************************
 * Method: cleanupBullets
 * Description: Removes any dead bullets
 **********************************************************************/
void Game::cleanupBullets()
{
   list<Bullet>::iterator it = m_bullets.begin();
   while (it != m_bullets.end())
   {
      if (it->isAlive())
      {
         ++it;
      }
      else
      {
         it = m_bullets.erase(it);
      }
   }
}

/**********************************************************************
* Method: cleanupRocks
* Description: Removes any dead or null rocks
**********************************************************************/
void Game::cleanupRocks()
{
   list<Rock*>::iterator it = m_rocks.begin();

   while (it != m_rocks.end())
   {
      Rock* pRock = *it;

      if (pRock != NULL && pRock->isAlive())
      {
         ++it;
      }
      else
      {
         if (pRock != NULL)
         {
            delete pRock;
            pRock = NULL;
         }

         it = m_rocks.erase(it);
      }
   }
}

/**********************************************************************
* Method: initializeRocks
* Description: Creates a new set of rocks
**********************************************************************/
void Game::initializeRocks()
{
   for (int i = 0; i < START_ROCK_COUNT; i++)
   {
      Point startPoint = getRandomPoint(m_topLeft, m_bottomRight);
      float angle = random(MIN_ANGLE, MAX_ANGLE);

      m_rocks.push_back(new BigRock(startPoint, angle));
   }
}

/**********************************************************************
 * Method: advanceRocks
 * Description: Advances the rocks.
 **********************************************************************/
void Game::advanceRocks()
{
   // In case we've killed off all the rocks at some point
   // we reinitialize them
   if (m_rocks.size() <= 0)
      initializeRocks();

   for (list<Rock*>::iterator rock = m_rocks.begin();
      rock != m_rocks.end(); ++rock)
   {
      if (*rock != NULL)
         (*rock)->advance();
   }
}

/**********************************************************************
 * Method: advanceBullets
 * Description: Advances the bullets
 **********************************************************************/
void Game::advanceBullets()
{
   for (list<Bullet>::iterator it = m_bullets.begin();
      it != m_bullets.end(); ++it)
      it->advance();
}

/**********************************************************************
* Method: HANDLE COLLISIONS
* Description: Checks to see if any collisions occurred and takes
* care of them.
**********************************************************************/
 void Game::handleCollisions()
 {
    // If there are any bullets, check to see if they collided
    // We check bullets first to give the user a slight advantage
    // as we might destroy a rock just moments before the ship hits it
    for (list<Bullet>::iterator it = m_bullets.begin();
       it != m_bullets.end(); ++it)
    {
       if (HIT == handleCollisions(*it))
          m_score++;
    }

    // If the ship is dead, the game is over and this no longer
    // matters
#ifndef INVINCIBLE
    if (m_ship.isAlive())
    {
       if (HIT == handleCollisions(m_ship) && m_lives > 0)
          m_lives--;
    }
#endif

 }

 /**********************************************************************
 * Method: HANDLE COLLISIONS
 * Description: Checks to see if any collisions occurred between a
 * specific flying object and all of the rocks on screen
 **********************************************************************/
 int Game::handleCollisions(FlyingObject & obj)
 {
    // We're going to iterate through our rocks and check each one
    // to see if it collides with the object (obj)
    list<Rock*>::iterator it = m_rocks.begin();

    while (it != m_rocks.end())
    {
       Rock* pRock = *it;

       // We really shouldn't have any null pointers, but just in case
       // we skip over the rock and move on to the next; such NULL
       // rocks can be cleaned up in the cleanupRocks
       assert(pRock != NULL);
       if (pRock == NULL)
       {
          ++it;
          continue;
       }

       // Now, we get the closest distance and we check to see if it is
       // within the sum of the radii of the rock and the object
       float closestDistance = getClosestDistance(obj, *pRock);

       if (closestDistance <= (obj.getRadius() + pRock->getRadius()))
       {
          // If it is, we kill the object - bye bye!!
          obj.kill();

          // Then, we hit the rock, which kills it and will possibly break it into
          // fragments, which we add just before the current rock
          // (i.e. the rock we just hit)
          list<Rock*> * frags = pRock->hit();
          if (NULL != frags)
          {
             // By adding these before the current rock, we avoid
             // problems with our iterator; plus, we're using a 
             // list, so we can safely do this
             m_rocks.splice(it, *frags);
             delete frags;
             frags = NULL;
          }

          // And exit because we can only collide with an object once
          return HIT;
       }
       else
       {
          ++it;
       }
    }

    return MISS;
 }

 /**********************************************************************
 * Method: handleInput
 * Description: Handles user input
 **********************************************************************/
void Game::handleInput(const Interface &pUI)
{
   if (!m_ship.isAlive())
      return;

   if (pUI.isRight())
   {
      m_ship.rotateRight();
   }

   if (pUI.isLeft())
   {
      m_ship.rotateLeft();
   }

   if (pUI.isUp())
   {
      m_ship.thrust();
   }

   if (pUI.isSpace())
   {
      m_bullets.push_back(m_ship.fire());
   }
}

/**********************************************************************
 * Method: draw
 * Description: Draws game objects on the screen
 **********************************************************************/
void Game::draw(const Interface &pUI)
{
   if (m_ship.isAlive())
      m_ship.draw();

   drawBullets();

   drawRocks();

   drawScore();

   drawLives();
}

/**********************************************************************
 * Method: drawRocks
 * Description: Draws rocks
 **********************************************************************/
void Game::drawRocks()
{
   for (list<Rock*>::iterator rock = m_rocks.begin();
      rock != m_rocks.end(); ++rock)
      (*rock)->draw();
}

/**********************************************************************
 * Method: drawBullets
 * Description: Draws bullets
 **********************************************************************/
void Game::drawBullets()
{
   for (list<Bullet>::iterator bullet = m_bullets.begin();
      bullet != m_bullets.end(); ++bullet)
      bullet->draw();
}

/**********************************************************************
* Method: drawScore
* Description: Draws the score on the screen
**********************************************************************/
void Game::drawScore() const
{
   stringstream ss;
   ss << "Points: " << m_score;
   drawText(getScoreLocation(), ss.str().c_str());
}

/**********************************************************************
 * Method: drawLives
 * Description: Draws remaining lives on the screen
 **********************************************************************/
void Game::drawLives() const
{
   stringstream ss;
   ss << "Lives: " << m_lives;
   drawText(getLivesLocation(), ss.str().c_str());
}

/**************************************************************************
* GAME :: GET SCORE LOCATION
* Gets a location to draw the score for the game
**************************************************************************/
Point Game::getScoreLocation() const
{
   return Point(
      m_topLeft.getX() + SCORE_X_OFFSET,
      m_topLeft.getY() + SCORE_Y_OFFSET
   );
}

Point Game::getLivesLocation() const
{
   return Point(
      m_topLeft.getX() + LIVES_X_OFFSET,
      m_topLeft.getY() + LIVES_Y_OFFSET
   );
}

/**************************************************************************
* GAME :: GET RANDOM POINT
* Gets a random point between two other points; think of the two points
* defining a plane; this returns a random point somewhere on that plane
**************************************************************************/
Point Game::getRandomPoint(const Point & in_topLeft, const Point & in_bottomRight)
{
   assert(in_topLeft.getX() <= in_bottomRight.getX());
   assert(in_bottomRight.getY() <= in_topLeft.getY());

   // Choose random x and y coordinates and create a point from them
   float x = random(in_topLeft.getX(), in_bottomRight.getX());
   float y = random(in_bottomRight.getY(), in_topLeft.getY());
   return Point(x, y);
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() - (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() - (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() - (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() - (obj2.getVelocity().getDy() * i / dMax));
      
      distMin = min(distMin, point1 - point2);
   }
   
   return distMin;
}

