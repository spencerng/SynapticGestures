#include <iostream>
#include <vector>
#include <cmath>
#include "Containers.h"
#include "trackpadMovement.h"

#define MAX_TIMES_CALLED    10
#define EPSILON				30
#define PI 					3.14159265

static int times_called = 0; //number of times determineMovement is called
std::vector< Point<long> > _deltas(5); //storage of deltas - only fills while the function is only recording data
enum types { swipeUP = 0, swipeDOWN = 1, swipeLEFT = 2, swipeRIGHT = 3, flickUP = 4, flickDOWN = 5, flickLEFT = 6, flickRIGHT = 7, TAP = 8, none = 9 }; //all possible types of gestures
enum DIR { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 }; //all directions

													/*
													DIRECTIONS:
													up: deltaY negative
													down: deltaY positive
													left: deltaX negative
													right: deltaX positive
													*/

													//return direction trackpad is moving based on the change in x and change in y
int UDLR(int deltaX, int deltaY) {
	if (deltaX == 0 && deltaY == 0)
		return none;
	else if (abs(deltaX) < abs(deltaY) && deltaY > 0)
		return DOWN;
	else if (abs(deltaX) < abs(deltaY) && deltaY < 0)
		return UP;
	else if (abs(deltaX) > abs(deltaY) && deltaX > 0)
		return RIGHT;
	else if (abs(deltaX) > abs(deltaY) && deltaX < 0)
		return LEFT;
}

void onTouchStart() {
	times_called = 0;
}

//determine type of movement (tap, swipe, flick), and what direction, if applicable
int determineMovement(long deltaX, long deltaY, bool isReleased) {
	if (times_called <= MAX_TIMES_CALLED && times_called != -1) {
		if (isReleased) { //only record data for the maximum number of times it can be called
			times_called = -1;
			long sumDeltaX = 0;
			long sumDeltaY = 0;
			for (Point<long> nig : _deltas) {
				sumDeltaX += nig.x;
				sumDeltaY += nig.y;
			}

			long distance = sqrt(sumDeltaX * sumDeltaX + sumDeltaY * sumDeltaY); //look at overall movement
			_deltas.clear();
			if (distance < EPSILON) //tap
				return TAP;

			else { //flick
				int flick_dir = UDLR(sumDeltaX, sumDeltaY);
				if (flick_dir == UP) return flickUP;
				else if (flick_dir == DOWN) return flickDOWN;
				else if (flick_dir == LEFT) return flickLEFT;
				else if (flick_dir == RIGHT) return flickRIGHT;
				else return none;
			}
			
		}
		else if (times_called == MAX_TIMES_CALLED) {
			times_called = -1;
		}
		else {
			_deltas.push_back(Point<long>(deltaX, deltaY));
			times_called++;
			return -1;
		}
	}

	else { //swipe
		int swipe_dir = UDLR(deltaX, deltaY);
		if (swipe_dir == UP) 	   return swipeUP;
		else if (swipe_dir == DOWN) return swipeDOWN;
		else if (swipe_dir == LEFT) return swipeLEFT;
		else if (swipe_dir == RIGHT) return swipeRIGHT;
		else return none;
	}
}
