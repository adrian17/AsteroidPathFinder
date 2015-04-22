#include "map.h"

#include <random>

XY getRandXY(){
	static std::random_device device;
	static std::mt19937 engine(device());
	static std::uniform_int_distribution<unsigned long> dist;
	static std::uniform_int_distribution<unsigned long>::param_type x_range(0, COLUMNS - 1);
	static std::uniform_int_distribution<unsigned long>::param_type y_range(0, ROWS-1);
	int x = dist(engine, x_range);
	int y = dist(engine, y_range);
	return { x, y };
}

Map::Map()
{
	generate();
}

void Map::generate(){
	clear();

	int sz = ROWS * COLUMNS;
	int holes = (int)(sz * 0.10);

	for (int i = 0; i < holes; ){
		XY xy = getRandXY();
		if (getTile(xy) != Empty)
			continue;
		map[xy] = Sinkhole;
		i++;
	}
}

void Map::clear(){
	map.clear();

	map[getRandXY()] = Start;
	map[getRandXY()] = Goal;
}

Tile Map::getTile(int x, int y){
	if (x < 0 || y < 0 || x >= COLUMNS || y >= ROWS)
		return Sinkhole;
	if (map.find({ x, y }) == map.end())
		return Empty;
	return map[{x, y}];
}

void Map::setTile(int x, int y, Tile tile){
	if (x < 0 || y < 0 || x >= COLUMNS || y >= ROWS)
		return;
	map[{x, y}] = tile;
}