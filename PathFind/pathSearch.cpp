#include <algorithm>

#include "pathSearch.h"

template<typename Iterator, typename Val>
Iterator naive_lower_bound(Iterator begin, Iterator end, const Val &val){
	auto it = begin;
	while (it != end){
		if (!(*it < val))
			break;
		it++;
	}
	return it;
}

XY dirs[] = {
	{ -1, -1 },	{ -1, 0 },	{ -1, 1 },
	{ 0, -1 },				{ 0, 1 },
	{ 1, -1 },	{ 1, 0 },	{ 1, 1 }
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

	if (map.getTile(head) == Goal){
		success = true;
		return true;
	}

	paths.pop_back();

	traversed.insert(head);

	for (XY dir : dirs){
		XY newHead = { head.first + dir.first, head.second + dir.second };

		if (traversed.find(newHead) != traversed.end())
			continue;

		auto tileOnHead = map.getTile(newHead);
		if (tileOnHead == Asteroid || tileOnHead == GravityWell || tileOnHead == Gravity)
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

		paths.insert(naive_lower_bound(paths.begin(), paths.end(), newPath), std::move(newPath));
	}

	return false;
}