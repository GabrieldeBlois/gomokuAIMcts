#pragma once
#include "Constant.h"
#include <array>
#include "Node.h"
#include "Position.h"

#define TOGGLE_PLAYER(x) (3 - x)

class Game
{
public:
	// array that that may contain one row of the board (or diag)
	typedef std::array<uint8_t, Const::TABSIZE> t_boardSide;

	// the board itself
	typedef std::array<t_boardSide, Const::TABSIZE> t_board;
	
	// a double array containing engough row as there is diag that may contain winning positions:
	// in the following example, only a three tick alignement should win:
	// o | * | o
	// * | o | * 
	// o | * | o
	// so for each diagonal direction, only the midle one may contain a winning alignement.
	typedef std::array<t_boardSide, Const::TABSIZE_DEVIDED> t_boardDivided;

	class State {
	public:
		State(int x, int y, int player);
		State(const State &cp);
		uint8_t x;
		uint8_t y;
		int player;
	};

public:
	Game();
	~Game();

	enum STATE
	{
		UNDEFINED = -1, // should not occur, its just in case
		DRAW, // game DRAW
		P1, // means P1 won
		P2 // means P2 won
	};

	static Game::STATE checkState(t_board const &tab);
	static void getEmptyBoardPosition(t_board const & const, std::vector<Position> &);
	// the board tow play actual game
	t_board _board = {};
	std::vector<Position> emptyPos;

	void performMove(State &);
	Game::STATE simulatePlayout(Node const *) const;
};

