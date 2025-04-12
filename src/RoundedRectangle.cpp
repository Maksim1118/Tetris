#include "RoundedRectangle.h"

#include <cmath>

#define PI 3.1415926535

using namespace sf;

RoundedRectangle::RoundedRectangle()
    :m_CornerPointCount(2), m_Radius(1.f)
{

}

size_t RoundedRectangle::getPointCount() const
{
    return m_CornerPointCount * 4;
}

Vector2f RoundedRectangle::getPoint(size_t index) const
{
    if (m_CornerPointCount == 1 || m_Radius == 0.0f)
    {
        RectangleShape rect(m_size);
        return rect.getPoint(index);
    }
    else
    {
        size_t corner = index / m_CornerPointCount;
        float angle = 0;
        bool isLastPointOnCorner = (index % m_CornerPointCount == m_CornerPointCount - 1);
        if (isLastPointOnCorner)
        {
            angle = 90.0f;
        }
        else
        {
            angle = (index % m_CornerPointCount) * m_AnglePerPoint;
        }
        Vector2f point;
        switch (corner)
        {
        case 0:
            point = { m_Radius, m_Radius };
            angle -= 180;
            break;
        case 1:
            point = { m_size.x - m_Radius, m_Radius };
            angle -= 90;
            break;
        case 2:
            point = { m_size.x - m_Radius, m_size.y - m_Radius };
            break;
        default:
            point = { m_Radius, m_size.y - m_Radius };
            angle += 90;
        }
        point += {cosf(angle* PI / 180)* m_Radius, sinf(angle* PI / 180)* m_Radius};
        return point;
    }

}

void RoundedRectangle::setSize(Vector2f size)
{
    m_size = size;
    update();
}

Vector2f RoundedRectangle::getSize()
{
    return m_size;
}

void RoundedRectangle::setRadius(float radius)
{
    m_Radius = radius;
    update();
}

float RoundedRectangle::getRadius()
{
    return m_Radius;
}

int RoundedRectangle::getCornerPointCount()
{
    return m_CornerPointCount;
}

void RoundedRectangle::setCornerPointCount(float points)
{
    m_CornerPointCount = points;
    m_AnglePerPoint = 90.0f / points;
    update();
}