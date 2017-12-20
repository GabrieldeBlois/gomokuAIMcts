#pragma once
#include "Constant.h"
#include <array>

enum STATE
{
	UNDEFINED = -1, // should not occur, its just in case
	IN_PROGRESS = 0,
	P1 = 1, // means P1 won
	P2 = 2, // means P2 won
	DRAW = 3 // game DRAW
};

class State {
public:
	State(int x, int y, int player, STATE state = STATE::IN_PROGRESS) : x(x), y(y), player(player), state(state) {}
	State(const State &cp) : x(cp.x), y(cp.y), state(cp.state) {}
	uint8_t x;
	uint8_t y;
	int player;
	STATE state;
};