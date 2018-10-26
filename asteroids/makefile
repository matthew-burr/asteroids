###############################################################
# Program:
#     Project 13, Asteroids
#     Brother McCracken, CS165
# Author:
#     Matthew Burr
# Summary:
#     The finished Asteroids project. Has full game function
#	  plus some additional capabilities. Fly the ship around,
#	  shoot rocks, earn points.
# Above and Beyond
#     1. Added a score
#		a. Added a member variable to Game to track the score
#		b. Added a function to Game to locate the score
#		c. Added a call to draw the score
#		Note: In the interest of not "over-architecting" this
#		I kept the score handling relatively simple
#	  2. Added operators to the Point class
#		a. Added an AddTo operator to make it easier to move
#		   a point by adding a Velocity
#		b. Added a Subtraction operator to make it easier to
#		   find the distance between two points
#		c. Adjusted functions to take advantage of these
#		   operators:
#			i. FlyingObject::Advance uses the AddTo to move
#			ii. getClosestDistance() uses the Subtraction to
#				find the distance between two points
#	  3. Added ship invulnerability to allow a brief period
#		 for the ship to be invulnerable in case it coexists
#		 in space with a rock when it is first created
#		a. Added fields to ship to track invulnerability
#		   and how long the ship has left to be invulnerable
#		b. Virtualized the kill function and overrode it in
#		   Ship to skip death if invulnerable
#		c. Added a function to turn on vulnerability for the
#		   ship, with a time limit
#		d. Adjusted the draw method to make the ship blink
#		   while its invulnerable
#	  4. Added multiple lives for the ship 
#		a. Added fields to track the number of lives
#		b. Added code to display remaining lives on the screen
#		c. Added code to handle recreating the ship for each
#		   life
#		d. Since multiple lives increase the possibility of
#		   killing all rocks, added code to create 5 new
#		   rocks when you've killed them all
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h velocity.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h bullet.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rocks.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
