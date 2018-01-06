
#ifndef UCT_HPP_
#define UCT_HPP_

#include <limits>
#include "Node.h"
#include <cmath>

#define INTEGER_MAX_VALUE ()

class Uct {
public:
	static double uctValue(int totVisit, double node, int nodeVisit) {
		return (nodeVisit == 0) ? 
			std::numeric_limits<int>::max() :
			(node / static_cast<double>(nodeVisit)) + 1.41f * sqrt(log(totVisit) / static_cast<double>(nodeVisit));
	}

	static Node * findBestNodeWithUCT(Node * node) {
		auto parentVisit = node->getVisitCount();

		auto result = &node->_child.front();

		// in the case where the first node is the biggest UCT value possible, no need to enter the loop
		if (uctValue(parentVisit, result->getWinScore(), result->getVisitCount()) == std::numeric_limits<int>::max())
			return result;

		/*
		double savedUctValue = 0;
		for (auto c : node->_child) {
			double tmpDPrime = 0;
			if ((tmpDPrime = uctValue(parentVisit, c.getWinScore(), c.getVisitCount())) > savedUctValue) {
				if (tmpDPrime == std::numeric_limits<int>::max())
					return &c;
				savedUctValue = tmpDPrime;
				result = &c;
			}
		}*/

		double savedUctValue = 0;
		for (uint8_t i = 0; i < node->_child.size(); ++i)
		{
			double tmpDPrime = 0;
			if ((tmpDPrime = uctValue(parentVisit, node->_child[i].getWinScore(), node->_child[i].getVisitCount())) > savedUctValue) {
				if (tmpDPrime == std::numeric_limits<int>::max())
					return &node->_child[i];
				savedUctValue = tmpDPrime;
				result = &node->_child[i];
			}

		}

		/*
		for (std::vector<Node>::iterator it = node->_child.begin(); it != node->_child.end(); ++it) {
			double tmpDPrime = 0;
			if ((tmpDPrime = uctValue(parentVisit,	it->getWinScore(), it->getVisitCount())) > savedUctValue) {
				if (tmpDPrime == std::numeric_limits<int>::max())
					return &(*it);
				savedUctValue = tmpDPrime;
				result = &(*it);
			}
		}*/

		return result;
	}
};

#endif /* end of include guard: UCT_HPP_ */