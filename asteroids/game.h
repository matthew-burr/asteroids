/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "uiInteract.h"
#include "point.h"
#include <list>
#include "rocks.h"
#include "ship.h"

class Game
{
public:
   Game(Point tl, Point br);
   ~Game();

   void advance();
   
   void handleInput(const Interface &pUI);
   void draw(const Interface &pUI);

private:
   Point m_topLeft;
   Point m_bottomRight;
   std::list<Rock*> m_rocks;
   std::list<Bullet> m_bullets;
   Ship m_ship;
   int m_score;
   int m_lives;
   Point m_scoreLocation;

   void initializeRocks();
   void advanceRocks();
   void advanceBullets();
   void handleCollisions();
   int handleCollisions(FlyingObject & obj);
   void cleanupZombies();
   void cleanupBullets();
   void cleanupRocks();
   void drawRocks();
   void drawBullets();
   void drawScore() const;
   void drawLives() const;
   Point getScoreLocation() const;
   Point getLivesLocation() const;
   static Point getRandomPoint(const Point & in_topLeft, const Point & in_bottomRight);
   float getClosestDistance(const FlyingObject & obj1, const FlyingObject & obj2) const;
};


#endif /* GAME_H */
