#pragma once

#include "Position.h"
#include "Game.h"
#include <chrono>
#include "Uct.h"

class Mcts {
public:
	Position findNextMove(const Game &game, uint8_t player) {
		Node * rootNode = &Node(State(0, 0, TOGGLE_PLAYER(player)), nullptr);
		//rootNode._parent = nullptr;
		//rootNode.state.player = TOGGLE_PLAYER(player);
		//rootNode.state.state = STATE::IN_PROGRESS;
		auto start = std::chrono::system_clock::now();
		
		auto counter = 0;

		// the AI will have 4 seconds to answer the desired position
		// monte carlo tree search consists of 4 stages: 
		// Selection		-> select the tree node that will be expansed (thnaks to the UCT algo)
		// Expansion		-> add all of the possible move to the selected node
		// Simulation		-> take one random child node and simulate a random playout
		// backpropagation	-> set all the winScore and visitCount accordingly to what has just been done
		while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() < 4) {
		
			// selection
			Node * targetNode = selectTargetNode(rootNode);

			// expansion
			if (targetNode->state.state == STATE::IN_PROGRESS)
				expandNode(targetNode, game);

			// simulation
			if (targetNode->_child.size() > 0)
				targetNode = targetNode->getRandomChild();

			auto simulationResult = game.simulatePlayout(targetNode);

			// backpropagation
			backPropagation(targetNode, simulationResult);

			++counter;
		}
		std::cout << "Done with : " << counter << " simulations";

		Node * tmpResult = rootNode->getChildWithMaxScore();

		// return it as position
		return { tmpResult->state.x, tmpResult->state.y };
	}

	void backPropagation(Node * tmp, STATE s) {

		while (tmp) {
			tmp->incrementVisit();
			if (static_cast<STATE>(tmp->state.player) == s)
				tmp->incrementWinScore();
			tmp = tmp->_parent;
		}
	}

	void expandNode(Node * targetNode, const Game & g) {
		for (auto p : g.board.getEmptyPosition()) {
			targetNode->_child.push_back(Node(State(p.x, p.y, TOGGLE_PLAYER(targetNode->state.player)), targetNode));
		}
	}

	Node * selectTargetNode(Node * root) {
		while (root->_child.size() != 0) {
			root = Uct::findBestNodeWithUCT(root);
		}
		return root;
	}


private:
};