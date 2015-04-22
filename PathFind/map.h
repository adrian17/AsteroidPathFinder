#pragma once

#include <unordered_map>
#include <array>

#include "path.h"

enum Tile
{
	Empty,
	Sinkhole,
	Start,
	Goal
};

const std::unordered_map<Tile, std::array<int, 3>, std::hash<int>> colors = {
	{ Empty, { 128, 128, 128 } },
	{ Sinkhole, {0, 0, 0} },
	{ Start, { 0, 0, 255 } },
	{ Goal, { 0, 0, 255 } }
};

const int COLUMNS = 80, ROWS = 60;

class Map
{
public:
	Map();

	void generate();

	XY getStart(){
		for (auto& kv : map)
			if (kv.second == Start)
				return kv.first;
		return{ 0, 0 };
	}

	XY getGoal(){
		for (auto& kv : map)
			if (kv.second == Goal)
				return kv.first;
		return{ 0, 0 };
	}

	Tile getTile(int x, int y);
	Tile getTile(XY xy){
		return getTile(xy.first, xy.second);
	}

	void setTile(int x, int y, Tile tile);
	void setTile(XY xy, Tile tile){
		setTile(xy.first, xy.second, tile);
	}

private:
	std::unordered_map<XY, Tile> map;
};

