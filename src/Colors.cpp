#include "Colors.h"
using namespace sf;
using namespace std;

const Color black = { 0,0,0 };
const Color orange = { 226, 116, 17 };
const Color green = { 0,255, 0 };
const Color red = { 255, 0, 0 };
const Color yellow = { 255, 255, 0 };
const Color purple = { 166, 0, 247 };
const Color pink = { 252, 15, 192 };
const Color blue = { 13, 64, 216 };
const Color lightGray = { 200,200,200 };
const Color yellow_green = { 154, 205, 50 };
const Color denimBlue = { 21, 96, 189 };
const Color darkGreen = { 0, 105, 62 };
const Color white = { 255,255,255 };

const Colors getTetColors()
{
	return {orange, green, red, yellow, purple, pink, blue };
}