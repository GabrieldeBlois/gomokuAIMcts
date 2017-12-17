#pragma once

#include "Node.h"
#include "Game.h"
#include <vector>

class Node
{
public:
	explicit Node(const Game::State &state, Node *parent = nullptr) :
		state(state),
		_parent(parent),
		_child(std::vector<Node>())
	{
	}

	Node(const Node &cp) :
		state(cp.state),
		_parent(cp._parent),
		_child(std::vector<Node>(cp._child))
	{
	}

	~Node()
	{
	}

	// I know its dirty to make a public member like this but its a little school projet btw
	Game::State state;
	Node *_parent;
	std::vector<Node> _child;
};

