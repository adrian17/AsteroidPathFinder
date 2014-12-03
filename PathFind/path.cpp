#include "path.h"

#include <algorithm>
#include <iostream>

heuteristics_mode dist_mode = EUCLIDAN;

double dist_euclidan(XY xy, XY xy2){
	int x1 = xy.first, y1 = xy.second;
	int x2 = xy2.first, y2 = xy2.second;
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double dist_manhattan(XY xy, XY xy2){
	int x1 = xy.first, y1 = xy.second;
	int x2 = xy2.first, y2 = xy2.second;
	return abs(x2 - x1) + abs(y2 - y1);
}

double dist_octile(XY xy, XY xy2){
	int x1 = xy.first, y1 = xy.second;
	int x2 = xy2.first, y2 = xy2.second;
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	return std::max(dx, dy) + (sqrt(2) - 1) * std::min(dx, dy);
}

double heuteristics_dist(XY xy, XY xy2){
	if (dist_mode == MANHATTAN)
		return dist_manhattan(xy, xy2);
	else if (dist_mode == EUCLIDAN)
		return dist_euclidan(xy, xy2);
	else if (dist_mode == OCTILE)
		return dist_octile(xy, xy2);
	else
		return 0;
}

double total_length(Path &path){
	double ret = 0;
	for (size_t i = 0; i < path.size() - 1; ++i)
		ret += dist_euclidan(path[i], path[i + 1]);
	return ret;
}