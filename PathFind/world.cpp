#include "world.h"

#include <string>
#include <algorithm>

World::World() :
	solver(map)
{}

void World::handleMouseClick(int x, int y, bool first_click){
	int tileX = x / (800 / COLUMNS), tileY = y / (600 / ROWS);
	static Tile currentMode;
	Tile tile = map.getTile(tileX, tileY);
	if (first_click)
		currentMode = tile;
	if (tile == Empty && currentMode == Empty)
		map.setTile(tileX, tileY, Sinkhole);
	else if (tile == Sinkhole && currentMode == Sinkhole)
		map.setTile(tileX, tileY, Empty);
	success = false;
	solver.reset();
}

void World::handleKeyboard(int key){
	if (key == SDLK_SPACE)
		finished = !finished;
	if (key == SDLK_r){
		map.generate();
		solver.reset();
		success = false; finished = false;
	}
	if (key == SDLK_d){
		dist_mode = (heuteristics_mode)((dist_mode + 1) % 3);
		solver.reset();
		success = false; finished = false;
	}
	if (key == SDLK_m){
		show_steps = !show_steps;
		solver.reset();
		success = false; finished = false;
	}
	if (key == SDLK_c) {
		map.clear();
		solver.reset();
		success = false; finished = false;
	}
}

void World::update(){
	if (show_steps){
		if (!finished)
			finished = solver.step(success);
	}
	else
		if (!success)
			solver.solve(success);
}

void World::draw(SDL_Window *window, SDL_Renderer *ren){
	float sw = 800 / COLUMNS;
	float sh = 600 / ROWS;

	PathObj pathObj = solver.getCurrentPath();
	Path &path = pathObj.vec;
	const auto &traversed = solver.getTraversed();

	int sz = path.size();
	for (int i = 0; i < sz; ++i) {
		auto xy = path[i];
		path.emplace_back(xy.first + 1, xy.second);
		path.emplace_back(xy.first, xy.second + 1);
		path.emplace_back(xy.first + 1, xy.second + 1);
	}

	SDL_SetWindowTitle(window, std::to_string(pathObj.length).c_str());

	for (int y = 0; y < ROWS; ++y){
		for (int x = 0; x < COLUMNS; ++x){
			int locx = (int)(x * sw), locy = (int)(y * sh);
			SDL_Rect rect = { locx + 1, locy + 1, (int)sw - 1, (int)sh - 1 };

			Tile tile = map.getTile(x, y);

			auto rgb = colors.at(tile);
			int r = rgb[0], g = rgb[1], b = rgb[2];

			if (tile == Empty)
				if (std::find(path.begin(), path.end(), XY(x, y)) != path.end())
					g += 120;
				else if (traversed.count({ x, y }) == 1)
					g += 60;

			SDL_SetRenderDrawColor(ren, r, g, b, 255);

			SDL_RenderFillRect(ren, &rect);
		}
	}
}