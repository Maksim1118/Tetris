#include "Resolutions.h"

std::array<sf::Vector2u, 5> Resolutions = 
{ {
    {1080, 1080},
    {920, 920},
    {800, 800},
    {720, 720},
    {600, 600}
} };

const std::array<sf::Vector2u, 5>& getResolutions() {
    return Resolutions;
}