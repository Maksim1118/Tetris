#include <SFML/Graphics.hpp>
#include <ctime>

#include "Game.h"
using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1080, 1080 }), "SFML works!", Style::Close | Style::Titlebar);
    
    srand(time(nullptr));
    Game game;

    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            game.handleEvent(event);
        }
        float deltaTime = clock.restart().asSeconds();
        game.timeElapsed(deltaTime);

        window.clear();
        game.draw(window);
        window.display();
    }
}