#include "ToogleButton.h"

using namespace sf;

ToogleButton::ToogleButton(Texture& normal, Texture& pressed)
    :Button(normal, pressed)
{

}

void ToogleButton::updateState(const Vector2f mousePos)
{
    switch (m_State)
    {
    case ButtonState::IDLE:
    {
        if (isPos(mousePos) && Mouse::isButtonPressed(Mouse::Left))
        {
            m_State = ButtonState::PRESSED;
            switchTexture();
        }
        break;
    }
    case ButtonState::PRESSED:
    {
        if (!Mouse::isButtonPressed(Mouse::Left))
        {
            m_State = ButtonState::RELEASED;
        }
        break;
    }
    case ButtonState::RELEASED:
    {
        if (isPos(mousePos) && Mouse::isButtonPressed(Mouse::Left))
        {
            m_State = ButtonState::PRESSED;
            switchTexture();
        }
        else if (!isPos(mousePos))
        {
            m_State = ButtonState::IDLE;
        }
        break;
    }
    default:
        break;
    }
}