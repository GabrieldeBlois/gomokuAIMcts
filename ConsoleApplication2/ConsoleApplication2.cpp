// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "Mcts.h"


int main()
{
	Game game = Game();
	Mcts ia = Mcts();
	uint8_t player = 1;
	while (1) {
		player = TOGGLE_PLAYER(player);
		Position p = ia.findNextMove(game, player);
		game.board.performMove(p, player);
		game.dumpBoard(game.board.getBoard());
	}
	

	system("pause");

	return 0;
}
