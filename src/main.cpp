#include <SFML/Graphics.hpp>
#include <ctime>

#include "Game.h"
#include "Colors.h"
#include "Variables.h"
#include "ResourceManager.h"
#include "RoundedRectangle.h"
using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1080, 1080 }), "SFML works!", Style::Close | Style::Titlebar);
    
    srand(time(nullptr));

    ResourceManager::getInstance().load();
        
    RoundedRectangle roundRectScore;
    roundRectScore.setSize(rectScoreSize);
    roundRectScore.setPosition(rectScorePos);
    roundRectScore.setRadius(rectScoreRadius);
    roundRectScore.setFillColor(lightGray);
    roundRectScore.setOutlineColor(yellow_green);
    roundRectScore.setOutlineThickness(rectScoreOutlineThickness);
    roundRectScore.setCornerPointCount(rectScorePointCount);

    Text scoreTitle;
    scoreTitle.setFont(ResourceManager::getInstance().getFont(FontName::SCORE));
    scoreTitle.setCharacterSize(scoreTitleSize);
    scoreTitle.setFillColor(darkGreen);
    scoreTitle.setString("< score >");
    float scoreTitleOffsetX = (rectScoreSize.x - scoreTitle.getLocalBounds().width) / 2.f;
    float scoreTitleOffsetY = 50.f;
    scoreTitle.setPosition(rectScorePos.x - rectScoreOutlineThickness + scoreTitleOffsetX, rectScorePos.y - rectScoreOutlineThickness + scoreTitleOffsetY);

    Text score;
    score.setFont(ResourceManager::getInstance().getFont(FontName::SCORE));
    score.setCharacterSize(scoreSize);
    score.setFillColor(darkGreen);


    RoundedRectangle roundRectNextTet;
    roundRectNextTet.setSize(rectNextTetSize);
    roundRectNextTet.setPosition(rectNextTetPos);
    roundRectNextTet.setRadius(rectNextTetRadius);
    roundRectNextTet.setFillColor(lightGray);
    roundRectNextTet.setOutlineColor(yellow_green);
    roundRectNextTet.setOutlineThickness(rectNextTetOutlineThickness);
    roundRectNextTet.setCornerPointCount(rectNextTetPointCount);

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

        window.clear(denimBlue);
        window.draw(roundRectScore);
        window.draw(roundRectNextTet);
        window.draw(scoreTitle);
        score.setString(to_string(game.getScore()));
        float scoreOffsetX = (rectScoreSize.x - score.getLocalBounds().width) / 2.f;
        float scoreOffsetY = (rectScoreSize.y - scoreTitle.getLocalBounds().height + scoreTitleOffsetY) / 2.f;
        score.setPosition(rectScorePos.x - rectScoreOutlineThickness + scoreOffsetX, rectScorePos.y - rectScoreOutlineThickness + scoreOffsetY);
        window.draw(score);
        game.draw(window);
        window.display();
    }
}