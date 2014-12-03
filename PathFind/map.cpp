#include "map.h"

#include <random>

XY getRandXY(){
	static std::mt19937 engine((std::random_device()()));
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
	map.clear();

	map[getRandXY()] = Start;
	map[getRandXY()] = Goal;

	int sz = ROWS * COLUMNS;
	int asteroids = (int)(sz * 0.10);
	int gravity_wells = (int)(sz * 0.05);

	for (int i = 0; i < asteroids; ){
		XY xy = getRandXY();
		if (getTile(xy) != Empty)
			continue;
		map[xy] = Asteroid;
		i++;
	}
	for (int i = 0; i < gravity_wells; ){
		XY xy = getRandXY();
		if (getTile(xy) != Empty)
			continue;
		for (int x = -1; x <= 1; ++x)
			for (int y = -1; y <= 1; ++y)
				if (getTile(xy.first+x, xy.second+y) == Empty)
					map[{xy.first+x, xy.second+y}] = Gravity;
		map[xy] = GravityWell;
		i++;
	}
}

Tile Map::getTile(int x, int y){
	if (x < 0 || y < 0 || x >= COLUMNS || y >= ROWS)
		return Asteroid;
	if (map.find({ x, y }) == map.end())
		return Empty;
	return map[{x, y}];
}

void Map::setTile(int x, int y, Tile tile){
	if (x < 0 || y < 0 || x >= COLUMNS || y >= ROWS)
		return;
	map[{x, y}] = tile;
}