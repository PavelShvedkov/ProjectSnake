#include "Snake.h"

Snake::Snake()
{
	int turn[2] = { 0,0 };
	Array turnA(turn, 2);
	Array start(2);
	start[0] = 2;
	start[1] = 2;
	this->coords = coords;
	length = 1;
	lastTurn = turnA;
	direction = '0';
	
}

void Snake::changeDirektion()
{
}
