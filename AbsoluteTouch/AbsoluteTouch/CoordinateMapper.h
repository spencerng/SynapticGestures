#ifndef COORDINATE_MAPPER_H
#define COORDINATE_MAPPER_H

#include "Containers.h"

class CoordinateMapper
{
public:
    Point<long> TouchToScreenCoords(Point<long> touchPoint);
    void SetTouchpadRect(Rect<long> rect);
    void SetScreenRect(Rect<long> rect);

private:
    Point<long> ClampTouchPoint(Point<long> touchPoint);
    Rect<long> m_touchpadRect;
    Rect<long> m_screenRect;
};

#endif
