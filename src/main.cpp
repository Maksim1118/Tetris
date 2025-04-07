#include <SFML/Graphics.hpp>
#include <ctime>

#include "Field.h"
#include "Tets.h"
using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1080, 1080 }), "SFML works!");
    
    srand(time(nullptr));
    Field field;
    field.setPosition(Vector2f(0.f, 0.f));

    LTet ltet;
    ltet.setPosition(Vector2f(0.f, 0.f));
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
        ltet.draw(window);
        window.display();
    }
}