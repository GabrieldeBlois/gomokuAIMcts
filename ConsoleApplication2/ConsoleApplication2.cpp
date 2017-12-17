// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define WINALIGN (15)
#define TABSIZE (20)

// this means that every diags that are NOT long enough to contain a winning alignement should not be calculated
#define TABSIZE_DEVIDED (TABSIZE - WINALIGN)

static uint8_t diag0[TABSIZE_DEVIDED][TABSIZE]{ {UINT8_MAX } };
static uint8_t diag1[TABSIZE_DEVIDED][TABSIZE]{ {UINT8_MAX } };

static uint8_t diag2[TABSIZE_DEVIDED][TABSIZE]{ {UINT8_MAX } };
static uint8_t diag3[TABSIZE_DEVIDED][TABSIZE]{ {UINT8_MAX } };

// actual is the currently winning player (as index 1 or 2)
// UINT8MAX is to avoid processing some unasigned values as long as some diagonals do not take one array of legnth (like \0 for strings)
static inline uint8_t checkForWin(uint8_t (&tab)[TABSIZE]) {
	uint8_t actual = 0;
	uint8_t wini = 1;

	for (uint8_t i = 0; i < TABSIZE; ++i) {
		auto content = tab[i];

		if (actual != 0 && content == actual)
			++wini;
		else if (content == UINT8_MAX)
			return 0;
		else {
			wini = 1;
			actual = content;
		}
		if (wini == WINALIGN)
			return actual;
	}
	return 0;
}

static inline 

int main()
{
	uint8_t tab[TABSIZE][TABSIZE]{ {0 } };

	for (uint8_t i = 0; i < TABSIZE_DEVIDED; ++i) {
		memset(diag0[i], UINT8_MAX, TABSIZE);
		memset(diag1[i], UINT8_MAX, TABSIZE);
		memset(diag2[i], UINT8_MAX, TABSIZE);
		memset(diag3[i], UINT8_MAX, TABSIZE);
	}
	uint8_t resultWin = 0;

	for (uint8_t i = 0; i < TABSIZE; ++i) {

		// this it to process ONLY diags that have lengths > WINALIGN (optimization purpose)
		for (uint8_t diagIncr = 0; diagIncr < TABSIZE_DEVIDED && diagIncr + i < TABSIZE; ++diagIncr) {
			uint8_t decr = TABSIZE - i - 1;

			diag0[diagIncr][i] = tab[diagIncr + i][i];
			diag1[diagIncr][i] = tab[diagIncr + i][decr];
			diag2[diagIncr][i] = tab[i][diagIncr + i];
			diag3[diagIncr][i] = tab[i][decr - diagIncr];

			diag0[diagIncr][i] = 1;
		}
		resultWin |= checkForWin(tab[i]);
	}

	// check win for all diags
	for (auto i = 0; i < TABSIZE_DEVIDED; ++i) {
		resultWin |= checkForWin(diag0[i]);
		resultWin |= checkForWin(diag1[i]);
		resultWin |= checkForWin(diag2[i]);
		resultWin |= checkForWin(diag3[i]);
	}

	for (auto i = 0; i < TABSIZE; ++i) {
		for (auto j = 0; j < TABSIZE; ++j) {
			std::cout << static_cast<int>(tab[i][j]) << " ";
		}
		std::cout << std::endl;
	}

	if (resultWin != 0)
		std::cout << "win !!!!!!! - - - - - " << static_cast<int>(resultWin) << std::endl;

	system("pause");

	return 0;
}
