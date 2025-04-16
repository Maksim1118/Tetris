#include <SFML/Graphics.hpp>
#include <ctime>

#include "Game.h"
#include "Colors.h"
#include "Variables.h"
#include "ResourceManager.h"
#include "RoundedRectangle.h"
#include "Button.h"
#include "ToogleButton.h"
#include "OneTimeButton.h"
using namespace sf;
using namespace std;

const size_t SCREEN_W = 1080;
const size_t SCREEN_H = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_W, SCREEN_H }), "Tetris", Style::Close | Style::Titlebar);

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

    float scaleGameOverText = 1.f;
    float maxScaleGameOverText = 1.5f;
    float zoom = 0.2f;
    float stepTime = 1.f;
    Text gameOverText;
    gameOverText.setFont(ResourceManager::getInstance().getFont(FontName::GAMEOVER));
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);

    RoundedRectangle roundRectNextTet;
    roundRectNextTet.setSize(rectNextTetSize);
    roundRectNextTet.setPosition(rectNextTetPos);
    roundRectNextTet.setRadius(rectNextTetRadius);
    roundRectNextTet.setFillColor(lightGray);
    roundRectNextTet.setOutlineColor(yellow_green);
    roundRectNextTet.setOutlineThickness(rectNextTetOutlineThickness);
    roundRectNextTet.setCornerPointCount(rectNextTetPointCount);

    ToogleButton play(ResourceManager::getInstance().getTexture(TextureName::PLAY), ResourceManager::getInstance().getTexture(TextureName::PLAYPRESSED));
    play.setPosition(buttonPlayPos);

    OneTimeButton restart(ResourceManager::getInstance().getTexture(TextureName::RESTART), ResourceManager::getInstance().getTexture(TextureName::RESTARTPRESSED));
    restart.setPosition(buttonRestartPos);

    ToogleButton sound(ResourceManager::getInstance().getTexture(TextureName::SOUND), ResourceManager::getInstance().getTexture(TextureName::NOSOUND));
    sound.setPosition(buttonSoundPos);

    OneTimeButton exit(ResourceManager::getInstance().getTexture(TextureName::EXIT), ResourceManager::getInstance().getTexture(TextureName::EXITPRESSED));
    exit.setPosition(buttonExitPos);

    Game game;

    Clock clock;

    Vector2f mousePos;
    while (window.isOpen())
    {
        Event event;
        mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            exit.updateState(mousePos);
            if (event.type == Event::Closed || exit.isPressed())
                window.close();
            play.updateState(mousePos);
            if (play.isPressed())
            {
                game.pause();
            }
            else
            {
                game.play();
            }

            sound.updateState(mousePos);
            if (sound.isPressed())
            {
                game.soundOff();
            }
            else
            {
                game.soundOn();
            }

            restart.updateState(mousePos);
            if (restart.isPressed())
            {
                game.restart();
            }
            game.handleEvent(event);
        }
        float deltaTime = clock.restart().asSeconds();
        stepTime -= deltaTime;
        if (stepTime <= 0.f)
        {
            if (scaleGameOverText < maxScaleGameOverText)
                scaleGameOverText += zoom;
            else
                scaleGameOverText = 1.f;
            stepTime = 1.f;
        }
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
        play.draw(window);
        restart.draw(window);
        sound.draw(window);
        exit.draw(window);
        if (game.isGameOver())
        {
            gameOverText.setScale(scaleGameOverText, scaleGameOverText);
            gameOverText.setPosition(
                (SCREEN_W - gameOverText.getLocalBounds().width * scaleGameOverText) / 2.f,
                (SCREEN_H - gameOverText.getLocalBounds().height * scaleGameOverText) / 2.f);
            window.draw(gameOverText);
        }
        window.display();
    }
}