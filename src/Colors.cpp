#include "Colors.h"
using namespace sf;
using namespace std;

const Color orange = { 226, 116, 17 };
const Color green = Color::Green;
const Color red = Color::Red;
const Color yellow = Color::Yellow;
const Color purple = { 166, 0, 247 };
const Color pink = { 255, 190, 200 };
const Color blue = { 13, 64, 216 };

const Colors getColors()
{
	return { orange, green, red, yellow, purple, pink, blue };
}