#include "AbsoluteTouchCallback.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "InputHelper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"

#include <iostream>

void AbsoluteTouchCallback::SetTouchpadRect(Rect<long> touchpadRect)
{
    m_coordMapper.SetTouchpadRect(touchpadRect);
}

void AbsoluteTouchCallback::SetScreenRect(Rect<long> screenRect)
{
    m_coordMapper.SetScreenRect(screenRect);
}

void AbsoluteTouchCallback::SetSmoothingWeight(int weight)
{
    m_touchProcessor.SetWeight(weight);
}

void AbsoluteTouchCallback::SetSendClick(bool sendClick)
{
    m_sendClick = sendClick;
}

void AbsoluteTouchCallback::OnTouchStarted(Point<long> touchPt)
{
    Point<long> screenPt = TouchToScreen(touchPt);
    if (m_sendClick) {
        SendLeftDown(screenPt);
    } else {
        MoveCursor(screenPt);
    }
}

void AbsoluteTouchCallback::OnTouchMoved(Point<long> touchPt)
{
    MoveCursor(TouchToScreen(touchPt));
}

void AbsoluteTouchCallback::OnTouchEnded()
{
    if (m_sendClick) {
        SendLeftUp();
    }
    m_touchProcessor.TouchEnded();
	firstTouch = true;
}

long clamp(long num, int low, int hi) {
	if (num < low) {
		num = low;
	}
	else if (num > hi) {
		num = hi;
	}
	return num;
}

Point<long> AbsoluteTouchCallback::prevAbsPoint(0, 0);
Point<long> AbsoluteTouchCallback::prevRelPoint(0, 0);

Point<long> AbsoluteTouchCallback::TouchToScreen(Point<long> touchPt)
{
	//Point<long> avgPt = m_touchProcessor.Update(touchPt);
	long deltaX, deltaY;
	Point<long> newRelPoint;
	if (firstTouch) {
		deltaX = 0;
		deltaY = 0;
		firstTouch = false;
	}
	else {
		deltaX = touchPt.x - prevAbsPoint.x;
		deltaY = touchPt.y - prevAbsPoint.y;
	}
	std::cout << deltaX << ", " << deltaY << std::endl;
	newRelPoint.x = clamp(prevRelPoint.x + deltaX, 0, 4668);
	newRelPoint.y = clamp(prevRelPoint.y + deltaY, 0, 3729);

	std::cout << prevRelPoint.x << ", " << prevAbsPoint.x << ", " << prevRelPoint.y << ", " << prevRelPoint.y << std::endl;

	prevAbsPoint = touchPt;
	prevRelPoint = newRelPoint;
	
    Point<long> screenPt = m_coordMapper.TouchToScreenCoords(newRelPoint);
    return screenPt;
}
