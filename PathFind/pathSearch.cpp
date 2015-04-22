#include <algorithm>

#include "pathSearch.h"

XY dirs[] = {
				{ -1, 0 },
	{ 0, -1 },				{ 0, 1 },
				{ 1, 0 },
};

void Solver::solve(bool &success){
	while (!step(success))
		;
}

bool Solver::step(bool &success){
	if (paths.empty())
		return true;

	PathObj pathObj = paths.back();
	Path &path = pathObj.vec;
	XY head = path.back();

	if (map.getTile(head) == Goal ||
		map.getTile({ head.first + 1, head.second }) == Goal ||
		map.getTile({ head.first, head.second + 1 }) == Goal ||
		map.getTile({ head.first + 1, head.second + 1 }) == Goal)
	{
		success = true;
		return true;
	}

	paths.pop_back();

	traversed.insert(head);

	for (XY dir : dirs){
		XY newHead = { head.first + dir.first, head.second + dir.second };

		if (traversed.find(newHead) != traversed.end())
			continue;

		if (map.getTile(newHead) == Sinkhole ||
			map.getTile({newHead.first + 1, newHead.second}) == Sinkhole ||
			map.getTile({newHead.first, newHead.second + 1}) == Sinkhole ||
			map.getTile({newHead.first + 1, newHead.second + 1}) == Sinkhole)
			continue;

		auto other = std::find_if(paths.begin(), paths.end(),
			[&](PathObj &p){return p.vec.back() == newHead; });
		if (other != paths.end())
			if (other->length > pathObj.length + dist_euclidan(head, newHead))
				paths.erase(other);
			else
				continue;

		PathObj newPath;
		newPath.vec = path;
		newPath.distToEnd = heuteristics_dist(newHead, goalXY);
		newPath.vec.emplace_back(newHead);
		newPath.length = total_length(newPath.vec);

		paths.insert(std::lower_bound(paths.begin(), paths.end(), newPath), std::move(newPath));
	}

	return false;
}