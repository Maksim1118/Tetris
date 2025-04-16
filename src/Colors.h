#pragma once
#include <SFML/Graphics.hpp>
#include <array>

extern const sf::Color white;
extern const sf::Color black;
extern const sf::Color orange;
extern const sf::Color green;
extern const sf::Color red;
extern const sf::Color yellow;
extern const sf::Color purple;
extern const sf::Color pink;
extern const sf::Color blue;
extern const sf::Color lightGray;
extern const sf::Color yellow_green;
extern const sf::Color denimBlue;
extern const sf::Color darkGreen;

using Colors = std::array<sf::Color, 7>;

const Colors getTetColors();