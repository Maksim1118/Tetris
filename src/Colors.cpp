#include "Colors.h"
using namespace sf;
using namespace std;

const Color black = { 0,0,0 };
const Color orange = { 226, 116, 17 };
const Color green = { 0,255, 0 };
const Color red = { 255, 0, 0 };
const Color yellow = { 255, 255, 0 };
const Color purple = { 166, 0, 247 };
const Color pink = { 255, 190, 200 };
const Color blue = { 13, 64, 216 };

const Colors getColors()
{
	return { black, orange, green, red, yellow, purple, pink, blue };
}