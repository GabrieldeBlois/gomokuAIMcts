#pragma once

#include "State.h"
#include <vector>
#include "Random.h"

class Node
{
public:
	explicit Node(const State &state, Node *parent = nullptr) :
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

	Node * getRandomChild() {
		auto test = xorshf96() % _child.size();
		return &_child[test];
	}
	

	// I know its dirty to make a public member like this but its a little school projet btw
	// so as it is more optimized ...
	State state;

	// the parent node should be a pointer since reference cannot be null;
	Node *_parent;
	std::vector<Node> _child;

	int getVisitCount() const {
		return _visitCount;
	}

	int getWinScore() const {
		return _winScore;
	}

	void incrementWinScore() { _winScore += 10; }

	void incrementVisit() { ++_visitCount; }

	Node * getChildWithMaxScore() {
		auto result = &_child.front();
		
		for (auto i = 0; i < _child.size(); ++i)
		{
			if (_child[i]._winScore > result->_winScore)
				result = &_child[i];
		}
		return result;
	}

private:
	int _visitCount = 0;
	int _winScore = 0;
};

