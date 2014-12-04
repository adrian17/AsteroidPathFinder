#pragma once

#include <unordered_set>
#include <list>

#include "map.h"

class Solver{
public:
	Solver(Map &map) :
		map(map)
	{
		reset();
	};

	void reset(){
		traversed.clear();
		startXY = map.getStart();
		goalXY = map.getGoal();

		paths.clear();
		paths.emplace_back(startXY);
	}

	void solve(bool &success);

	bool step(bool &success);

	const std::unordered_set<XY>& getTraversed() const {
		return traversed;
	}

	PathObj getCurrentPath() const {
		return paths.empty() ? PathObj() : paths.back();
	}

private:
	Map &map;

	XY startXY;
	XY goalXY;

	std::unordered_set<XY> traversed;
	std::vector<PathObj> paths;
};