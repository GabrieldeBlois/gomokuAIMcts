
#ifndef UCT_HPP_
#define UCT_HPP_

#include <limits>
#include "Node.h"
#include <cmath>

#define INTEGER_MAX_VALUE ()

class Uct {
public:
	static double uctValue(int totVisit, double node, int nodeVisit) {
		if (nodeVisit == 0)
			return std::numeric_limits<int>::max();
		
		return (node / (double)nodeVisit) + 1.41f * sqrt(log(totVisit) / (double)nodeVisit);
	}

	static Node * findBestNodeWithUCT(Node * node) {
		int parentVisit = node->getVisitCount();

		Node * result = &node->_child.front();

		// in the case where the first node is the biggest UCT value possible, no need to enter the loop
		if (uctValue(parentVisit, result->getWinScore(), result->getVisitCount()) == std::numeric_limits<int>::max())
			return result;

		double savedUctValue = 0;
		/*for (auto c : node->_child) {
			double tmpDPrime = 0;
			if ((tmpDPrime = uctValue(parentVisit, c.getWinScore(), c.getVisitCount())) > savedUctValue) {
				if (tmpDPrime == std::numeric_limits<int>::max())
					return &c;
				savedUctValue = tmpDPrime;
				result = &c;
			}
		}*/
		
		for (std::vector<Node>::iterator it = node->_child.begin(); it != node->_child.end(); ++it) {
			double tmpDPrime = 0;
			if ((tmpDPrime = uctValue(parentVisit,	it->getWinScore(), it->getVisitCount())) > savedUctValue) {
				if (tmpDPrime == std::numeric_limits<int>::max())
					return &(*it);
				savedUctValue = tmpDPrime;
				result = &(*it);
			}
		}

		return result;
	}
};

#endif /* end of include guard: UCT_HPP_ */