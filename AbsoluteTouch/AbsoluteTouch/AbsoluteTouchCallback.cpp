#include "AbsoluteTouchCallback.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "InputHelper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"
#include "trackpadMovement.h"
#define WINVER 0x0500
#include <Windows.h>

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
	onTouchStart();
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

int getW() {
	return 0;
}

void AbsoluteTouchCallback::OnTouchEnded()
{
	long movement = (long) determineMovement(0, 0, true);
	std::cout << movement << std::endl;
	int w = getW();
	if (movement == 8) {
		INPUT Input;
		Input.type = INPUT_MOUSE;
		Input.mi.mouseData = 0;
		Input.mi.time = 0;
		Input.mi.dx = 0;
		Input.mi.dy = 0;

		if (w >= 4)
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		else if (w == 0)
			Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		else if (w == 1)
			Input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;

		SendInput(1, &Input, sizeof(INPUT));

		if (w >= 4)
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		else if (w == 0)
			Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		else if (w == 1)
			Input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;

		SendInput(1, &Input, sizeof(INPUT));
	}

	if (w < 4 && movement < 8 && movement != -1) {
		INPUT ip;
		// Set up a generic keyboard event.
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		ip.ki.dwFlags = 0; // 0 for key press
		if (w == 1) {
			if (movement == 0 || movement == 4)
				ip.ki.wVk = VK_UP;
			else if (movement == 1 || movement == 5)
				ip.ki.wVk = VK_DOWN;
			else if (movement == 2 || movement == 6)
				ip.ki.wVk = VK_LEFT;
			else
				ip.ki.wVk = VK_RIGHT;
		}
		else if (w == 0) {
			if (movement == 0 || movement == 4)
				ip.ki.wVk = 0x57;
			else if (movement == 1 || movement == 5)
				ip.ki.wVk = 0x53;
			else if (movement == 2 || movement == 6)
				ip.ki.wVk = 0x41;
			else
				ip.ki.wVk = 0x44;
		}

		std::cout << (long)SendInput(1, &ip, sizeof(INPUT)) << " wVk " << std::endl;

		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		std::cout << (long)SendInput(1, &ip, sizeof(INPUT)) << " wVk " << std::endl;
	}

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

	long movement = (long) determineMovement(deltaX, deltaY, false);
	std::cout << movement << std::endl;

	Point<long> screenPt;
	int w = getW();
	if (w < 4 || movement == 8) {
		screenPt = m_coordMapper.TouchToScreenCoords(prevRelPoint);
	}
	else {
		newRelPoint.x = clamp(prevRelPoint.x + deltaX, 0, 4668);
		newRelPoint.y = clamp(prevRelPoint.y + deltaY, 0, 3729);

		std::cout << prevRelPoint.x << ", " << prevAbsPoint.x << ", " << prevRelPoint.y << ", " << prevAbsPoint.y << std::endl;
		screenPt = m_coordMapper.TouchToScreenCoords(newRelPoint);
		prevRelPoint = newRelPoint;
	}

	if (w < 4 && movement < 8 && movement != -1) {
		INPUT ip;
		// Set up a generic keyboard event.
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		ip.ki.dwFlags = 0; // 0 for key press
		if (w == 1) {
			if (movement == 0 || movement == 4)
				ip.ki.wVk = VK_UP;
			else if (movement == 1 || movement == 5)
				ip.ki.wVk = VK_DOWN;
			else if (movement == 2 || movement == 6)
				ip.ki.wVk = VK_LEFT;
			else
				ip.ki.wVk = VK_RIGHT;
		}
		else if (w == 0) {
			if (movement == 0 || movement == 4)
				ip.ki.wVk = 0x57;
			else if (movement == 1 || movement == 5)
				ip.ki.wVk = 0x53;
			else if (movement == 2 || movement == 6)
				ip.ki.wVk = 0x41;
			else
				ip.ki.wVk = 0x44;
		}

		std::cout << (long)SendInput(1, &ip, sizeof(INPUT)) << " wVk " << std::endl;

		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		std::cout << (long)SendInput(1, &ip, sizeof(INPUT)) << " wVk " << std::endl;
	}

	prevAbsPoint = touchPt;

    return screenPt;
}
