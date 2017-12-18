#include "stdafx.h"
#include "Game.h"
#include <array>
#include <algorithm>
#include "Position.h"
#include "Random.h"

/*
**
**	GAME class is supposed to implement the game rules
**	all this game developpement must be done in a strict OOP
**	to be able to develop any games that may use a MCTS algorithm
**
*/

Game::Game()
{
	getEmptyBoardPosition(_board, emptyPos);
}


Game::~Game()
{
}

// static inititalization of tabs that will contain diags
static Game::t_boardDivided diag0 = { { UINT8_MAX } };
static Game::t_boardDivided diag1 = { { UINT8_MAX } };
static Game::t_boardDivided diag2 = { { UINT8_MAX } };
static Game::t_boardDivided diag3 = { { UINT8_MAX } };

// actual is the currently winning player (as index 1 or 2)
// UINT8MAX is to avoid processing some unasigned values as long as some diagonals do not take one array of legnth (like \0 for strings)
static inline uint8_t checkForWin(const std::array<uint8_t, Const::TABSIZE> &tab) {
	uint8_t actual = 0;
	uint8_t wini = 1;

	for (uint8_t i = 0; i < Const::TABSIZE; ++i) {
		auto content = tab[i];

		if (actual != 0 && content == actual)
			++wini;
		else if (content == UINT8_MAX)
			return 0;
		else {
			wini = 1;
			actual = content;
		}
		if (wini == Const::WINALIGN)
			return actual;
	}
	return 0;
}

Game::STATE Game::checkState(const t_board &tab)
{
	for (uint8_t i = 0; i < Const::TABSIZE_DEVIDED; ++i) {
		diag0 = { {UINT8_MAX} };
		diag1 = { {UINT8_MAX} };
		diag2 = { {UINT8_MAX} };
		diag3 = { {UINT8_MAX} };
	}
	uint8_t resultWin = 0;

	for (uint8_t i = 0; i < Const::TABSIZE; ++i) {

		// this it to process ONLY diags that have lengths > WINALIGN (optimization purpose)
		for (uint8_t diagIncr = 0; diagIncr < Const::TABSIZE_DEVIDED && diagIncr + i < Const::TABSIZE; ++diagIncr) {
			uint8_t decr = Const::TABSIZE - i - 1;

			// diag0 contains diags from top left to bottom right
			diag0[diagIncr][i] = tab[diagIncr + i][i];

			// diag1 constains diags from to right to bottom left
			diag1[diagIncr][i] = tab[diagIncr + i][decr];

			// diag2 contains diags from bottom left to top right
			diag2[diagIncr][i] = tab[i][diagIncr + i];

			// diag3 contains diags from bottom right to top left
			diag3[diagIncr][i] = tab[i][decr - diagIncr];

			diag0[diagIncr][i] = 1;
		}
		resultWin |= checkForWin(tab[i]);
	}

	// check win for all diags
	for (auto i = 0; i < Const::TABSIZE_DEVIDED; ++i) {
		resultWin |= checkForWin(diag0[i]);
		resultWin |= checkForWin(diag1[i]);
		resultWin |= checkForWin(diag2[i]);
		resultWin |= checkForWin(diag3[i]);
	}

	for (auto i = 0; i < Const::TABSIZE; ++i) {
		for (auto j = 0; j < Const::TABSIZE; ++j) {
			std::cout << static_cast<int>(tab[i][j]) << " ";
		}
		std::cout << std::endl;
	}

	if (resultWin != 0)
		std::cout << "win !!!!!!! - - - - - " << static_cast<int>(resultWin) << std::endl;

	system("pause");

	return Game::STATE();
}

void Game::getEmptyBoardPosition(t_board const & const board, std::vector<Position> &tab) {
	for (uint8_t i = 0; i < Const::TABSIZE; ++i) {
		for (uint8_t j = 0; j < Const::TABSIZE; ++j) {
			if (board[i][j] == 0)
				tab.push_back( {i, j} );
		}
	}
}

// the board to simulate playouts
static Game::t_board _simboard {};
	
Game::STATE Game::simulatePlayout(Node const *node) const
{
	// = with std::array trigger the copy ctor natively
	_simboard = _board;

	auto player = TOGGLE_PLAYER(node->state.player);

	// populate the simulation board with the tree branch being processed
	while (node) {
		Game::State const &st = node->state;
		_simboard[st.x][st.y] = st.player;
		node = node->_parent;
	}

	// get all the empty positions of the board
	std::vector<Position> emptyPosTab = ;

	// simulation - - - - - - -
	while (checkState(_simboard) != Game::STATE::UNDEFINED) {
		unsigned long test = xorshf96();
			
	}

	return DRAW;
}

// write in the board a the right place the number of the player
// delete the empty position from the vector
void Game::performMove(Game::State &s) {
	_board[s.y][s.x] = s.player;
	emptyPos.erase(std::remove(emptyPos.begin(), emptyPos.end(), Position {s.x, s.y}), emptyPos.end());
}

Game::State::State(const State& cp) : x(cp.x), y(cp.y) {}

Game::State::State(int x, int y, int player) : x(x), y(y), player(player) {}

