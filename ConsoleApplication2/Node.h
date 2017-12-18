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

	// cpy ctor
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
	// so as it is more optimized ...
	Game::State state;

	// the parent node should be a pointer since reference cannot be null;
	Node *_parent;
	std::vector<Node> _child;
};

