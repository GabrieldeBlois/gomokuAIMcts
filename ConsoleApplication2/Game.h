#pragma once
#include "Constant.h"
#include <array>
class Game
{
public:
	class State {
	public:
		State(int x, int y);
		State(const State &cp);
		int x;
		int y;
	};

public:
	Game();
	~Game();

	enum STATE
	{
		ERROR = -1, // should not occur, its just in case
		DRAW, // game DRAW
		P1, // means P1 won
		P2 // means P2 won
	};
	static Game::STATE checkState(uint8_t (&tab)[Const::TABSIZE][Const::TABSIZE]);

	
	// the board tow play actual game
	std::array<std::array<uint8_t, Const::TABSIZE>, Const::TABSIZE_DEVIDED> _board = { { UINT8_MAX } };

	Game::STATE simulatePlayout(int player);
};

