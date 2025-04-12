#include "SFML/Graphics.hpp"

class RoundedRectangle : public sf::Shape
{
public:
    RoundedRectangle();
    virtual size_t getPointCount() const override;
    virtual sf::Vector2f getPoint(size_t index) const override;
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize();
    void setRadius(float radius);
    float getRadius();
    int getCornerPointCount();
    void setCornerPointCount(float points);

private:
    size_t m_CornerPointCount;
    float m_AnglePerPoint;
    float m_Radius;
    sf::Vector2f m_size;
};