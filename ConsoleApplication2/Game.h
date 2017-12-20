#pragma once
#include "Constant.h"
#include <array>
#include "Node.h"
#include "Position.h"
#include "State.h"

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

	class Board {
	public:
		Board();
		Board(const Board &);
		~Board();

		void performMove(const Position p, uint8_t player);
		uint8_t getBoardAt(const Position p);
		const t_board &getBoard() const;
		const std::vector<Position> & const getEmptyPosition() const;

		bool operator==(const Position&) const;
		bool operator!=(const Position&) const;

	private:
		// member variable
		t_board board;
		std::vector<Position> emptyPos;

	};

public:
	Game();
	~Game();


	static STATE checkState(t_board const &tab);
	void dumpBoard(const t_board& b)  const;

	// the board tow play actual game
	Board board;

	STATE simulatePlayout(Node const *) const;
};

bool operator==(const Position& a, const Position& b) {
	return a.x == b.x && a.y == b.y;
}