#include "stdafx.h"
#include "Game.h"
#include <array>


Game::Game()
{
}


Game::~Game()
{
}

static std::array<std::array<uint8_t, Const::TABSIZE>, Const::TABSIZE_DEVIDED> diag0 = { { UINT8_MAX } };
static std::array<std::array<uint8_t, Const::TABSIZE>, Const::TABSIZE_DEVIDED> diag1 = { { UINT8_MAX } };
static std::array<std::array<uint8_t, Const::TABSIZE>, Const::TABSIZE_DEVIDED> diag2 = { { UINT8_MAX } };
static std::array<std::array<uint8_t, Const::TABSIZE>, Const::TABSIZE_DEVIDED> diag3 = { { UINT8_MAX } };

// actual is the currently winning player (as index 1 or 2)
// UINT8MAX is to avoid processing some unasigned values as long as some diagonals do not take one array of legnth (like \0 for strings)
static inline uint8_t checkForWin(std::array<uint8_t, Const::TABSIZE> &tab) {
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

Game::STATE Game::checkState(uint8_t (&tab)[Const::TABSIZE][Const::TABSIZE])
{
	for (uint8_t i = 0; i < Const::TABSIZE_DEVIDED; ++i) {
		diag0 = { 0 };
		diag1 = { 0 };
		diag2 = { 0 };
		diag3 = { 0 };
	}
	uint8_t resultWin = 0;

	for (uint8_t i = 0; i < Const::TABSIZE; ++i) {

		// this it to process ONLY diags that have lengths > WINALIGN (optimization purpose)
		for (uint8_t diagIncr = 0; diagIncr < Const::TABSIZE_DEVIDED && diagIncr + i < Const::TABSIZE; ++diagIncr) {
			uint8_t decr = Const::TABSIZE - i - 1;

			diag0[diagIncr][i] = tab[diagIncr + i][i];
			diag1[diagIncr][i] = tab[diagIncr + i][decr];
			diag2[diagIncr][i] = tab[i][diagIncr + i];
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

// the board to simulate playouts
static uint8_t simBoard[Const::TABSIZE][Const::TABSIZE]{ { 0 } };

Game::STATE Game::simulatePlayout(int player)
{
	// keep in mind that this kind of iterative loop will be unrolled by gcc's -O2
	for (auto i  = 0; i < Const::TABSIZE; ++i)
	{
		std::copy(std::begin(_board))
	}
	return STATE();
}

Game::State::State(const State& cp) : x(cp.x), y(cp.y) {}

Game::State::State(int x, int y) : x(x), y(y) {}

