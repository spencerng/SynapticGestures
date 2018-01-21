#include <iostream>
#include <vector>
#include <cmath>

#define MAX_TIMES_CALLED    5
#define EPSILON				3
#define PI 					3.14159265


static int times_called = 0; //number of times determineMovement is called
Point<long> deltas[5]; //storage of deltas - only fills while the function is only recording data
enum types { swipeUP = 0, swipeDOWN = 1, swipeLEFT = 2, swipeRIGHT = 3, flickUP = 4, flickDOWN = 5, flickLEFT = 6, flickRIGHT = 7, TAP = 8 }; //all possible types of gestures
enum DIR   { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 }; //all directions

/*
	DIRECTIONS:
		up: deltaY negative
		down: deltaY positive
		left: deltaX negative
		right: deltaX positive
*/

//return direction trackpad is moving based on the change in x and change in y
int UDLR(int deltaX, int deltaY) {
	if(deltaX < 0 && deltaY <= 0) { //either returns down or left
		if(atan(deltaY/deltaX) * 180/PI <= 45) return LEFT;
		else								   return DOWN;
	}

	else if(deltaX < 0 && deltaY >= 0) { //either returns up or left
		if(atan(deltaY/deltaX) * 180/PI <= 45) return LEFT;
		else								   return UP;
	}

	else if(deltaX > 0 && deltaY <= 0) { //either returns down or right
		if(atan(deltaY/deltaX) * 180/PI <= 45) return RIGHT;
		else								   return DOWN;
	}

	else if(deltaX > 0 && deltaY >= 0) { //either returns up or right
		if(atan(deltaY/deltaX) * 180/PI <= 45) return RIGHT;
		else								   return UP;
	}
}


//determine type of movement (tap, swipe, flick), and what direction, if applicable
int determineMovement(int w, long deltaX, long deltaY, bool isReleased) {
	times_called++; //increment number of times function is called
	if(isReleased) {
		if(times_called <= MAX_TIMES_CALLED) { //only record data for the maximum number of times it can be called
			deltas[times_called - 1] = (Point<long>(deltaX, deltaY)); 

			long  distance = sqrt(deltaX * deltaX + deltaY * deltaY); //look at overall movement
			if(distance < EPSILON) //tap
				return TAP;

			else { //flick
				int flick_dir = UDLR(deltaX, deltaY);
				if(flick_dir == UP) 	   return flickUP;
				else if(flick_dir == DOWN) return flickDOWN;
				else if(flick_dir == LEFT) return flickLEFT;
				else					   return flickRIGHT; 
			}
		}

		else { } //do nothing
	}

	else { //swipe
		int swipe_dir = UDLR(deltaX, deltaY);
		if(swipe_dir == UP) 	   return swipeUP;
		else if(swipe_dir == DOWN) return swipeDOWN;
		else if(swipe_dir == LEFT) return swipeLEFT;
		else					   return swipeRIGHT;
	}
}