#pragma once

#include <vector>
#include <utility>

typedef std::pair<int, int> XY;

namespace std	//for unordered_map, unordered_set
{
	template<>
	struct hash<XY>
	{
		size_t operator()(const XY &p) const {
			return p.first * 1000 + p.second;
		}
	};
}

typedef std::vector<XY> Path;

double dist_euclidan(XY xy, XY xy2);
double dist_manhattan(XY xy, XY xy2);
double dist_octile(XY xy, XY xy2);

enum heuteristics_mode { MANHATTAN, EUCLIDAN, OCTILE };
extern heuteristics_mode dist_mode;
double heuteristics_dist(XY xy, XY xy2);

double total_length(Path &path);

struct PathObj
{
	double length, distToEnd;
	Path vec;

	bool operator<(const PathObj &p2) const {
		return this->length + this->distToEnd >= p2.length + p2.distToEnd;
	}
};