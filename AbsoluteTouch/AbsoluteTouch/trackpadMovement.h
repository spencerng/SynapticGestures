#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "Containers.h"

#ifndef TRACKPAD_MOVEMENT
#define TRACKPAD_MOVEMENT

void onTouchStart();
int UDLR(int deltaX, int deltaY);

//determine type of movement (tap, swipe, flick), and what direction, if applicable
int determineMovement(long deltaX, long deltaY, bool isReleased);
#endif // !TRACKPAD_MOVEMENT