#include <SFML/Graphics.hpp>

#include "Field.h"
using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1080, 1080 }), "SFML works!");
    
    Field field;
    field.setPosition(Vector2f(0.f, 0.f));
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        field.draw(window);
        window.display();
    }
}