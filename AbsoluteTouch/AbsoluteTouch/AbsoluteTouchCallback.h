#ifndef ABSOLUTE_TOUCH_CALLBACK_H
#define ABSOLUTE_TOUCH_CALLBACK_H

#include "Containers.h"
#include "CoordinateMapper.h"
#include "InputHelper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"

class AbsoluteTouchCallback : public TouchCallback
{
public:
    void SetTouchpadRect(Rect<long> touchpadRect);
    void SetScreenRect(Rect<long> screenRect);
    void SetSmoothingWeight(int weight);
    void SetSendClick(bool sendClick);

private:
    void OnTouchStarted(Point<long> touchPt) override;
    void OnTouchMoved(Point<long> touchPt) override;
    void OnTouchEnded() override;
    Point<long> TouchToScreen(Point<long> touchPt);

    CoordinateMapper m_coordMapper;
    TouchProcessor m_touchProcessor;
    bool m_sendClick = false;
	
	static Point<long> prevAbsPoint;
	static Point<long> prevRelPoint;
	bool firstTouch = true;
};

#endif
