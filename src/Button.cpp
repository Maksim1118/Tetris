#include "Button.h"

#include "ResourceManager.h"

using namespace sf;

Button::Button(Texture& normal, Texture& pressed)
    :m_Normal(normal), m_Pressed(pressed), m_State(ButtonState::IDLE), m_isNormalState(true)
{
    m_CurrentSprite.setTexture(m_Normal);
}

void Button::setPosition(Vector2f pos)
{
    m_CurrentSprite.setPosition(pos);
}

void Button::setScale(float scale)
{
    m_CurrentSprite.setScale(scale, scale);
    setPosition(m_CurrentSprite.getPosition() * scale);
}

bool Button::isPressed()
{
    return !m_isNormalState;
}

void Button::draw(RenderTarget& window)
{
    window.draw(m_CurrentSprite);
}

void Button::switchTexture()
{
    m_isNormalState = !m_isNormalState;
    m_isNormalState ? m_CurrentSprite.setTexture(m_Normal) : m_CurrentSprite.setTexture(m_Pressed);
}

bool Button::isPos(const Vector2f mousePos)
{
    Vector2f butPos = m_CurrentSprite.getPosition();
    FloatRect butSize = m_CurrentSprite.getLocalBounds();
    return mousePos.x > butPos.x && mousePos.x < butPos.x + butSize.width
        && mousePos.y > butPos.y && mousePos.y < butPos.y + butSize.height;

}