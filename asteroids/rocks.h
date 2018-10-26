/*************************************************************
* File: rocks.h
* Author: Matthew Burr
*
* Description: Contains the declarations of the various types
*  of rocks in a game of asteroids
*************************************************************/

#ifndef rocks_h
#define rocks_h

#include "flyingObject.h"
#include "point.h"
#include <list>

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define DEFAULT_ROCK_SPEED 1

// Define the following classes here:
/*****************************************
* ROCK
* An abstract class that is the base of
* all Rock classes. A Rock is a FlyingObject
* that also rotates and, when hit, may
* fragment into other Rocks.
*****************************************/
class Rock : public FlyingObject
{
public:
   Rock();
   Rock(const Point &in_point, float in_angle);
   Rock(const Point &in_point, float dx, float dy);
   void launch(const Point &in_point, float in_angle);
   void launch(const Point &in_point, float dx, float dy);
   virtual std::list<Rock*> * hit();
   virtual void advance();

protected:
   virtual int getSpin() const = 0;
   int getRotation() const { return m_rotation; }
   virtual std::list<Rock*> * getFragments() = 0;

private:
   int m_rotation;
};


/*****************************************
* BIG ROCK
* A subclass of Rock representing a large
* Rock that moves slowly and breaks into
* 2 Medium and 1 Small Rock when hit.
*****************************************/
class BigRock : public Rock
{
public:
   BigRock() {};
   BigRock(const Point &in_point, float in_angle) 
      : Rock(in_point, in_angle) { };
   BigRock(const Point &in_point, float dx, float dy)
      : Rock(in_point, dx, dy) { };
   virtual std::list<Rock*> * getFragments();
   virtual void draw() const;
   virtual float getRadius() const { return BIG_ROCK_SIZE; }

protected:
   virtual int getSpin() const { return BIG_ROCK_SPIN; }
};


/*****************************************
* MEDIUM ROCK
* A subclass of Rock representing a medium
* Rock that breaks into 2 Small Rocks when hit.
*****************************************/
class MediumRock : public Rock
{
public:
   MediumRock() {};
   MediumRock(const Point &in_point, float in_angle) 
      : Rock(in_point, in_angle) { };
   MediumRock(const Point &in_point, float dx, float dy)
      : Rock(in_point, dx, dy) { };
   virtual std::list<Rock*> * getFragments();
   virtual void draw() const;
   virtual float getRadius() const { return MEDIUM_ROCK_SIZE; }

protected:
   virtual int getSpin() const { return MEDIUM_ROCK_SPIN; }
};


/*****************************************
* SMALL ROCK
* A subclass of Rock representing a small
* Rock that moves quickly and simply
* disappears leaving no fragments when 
* hit.
*****************************************/
class SmallRock : public Rock
{
public:
   SmallRock() {};
   SmallRock(const Point &in_point, float in_angle) 
      : Rock(in_point, in_angle) { };
   SmallRock(const Point &in_point, float dx, float dy)
      : Rock(in_point, dx, dy) {};
   virtual std::list<Rock*> * getFragments();
   virtual void draw() const;
   virtual float getRadius() const { return SMALL_ROCK_SIZE; }

protected:
   virtual int getSpin() const { return SMALL_ROCK_SPIN; }
};




#endif /* rocks_h */
