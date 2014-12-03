#pragma once

#include "SDL.h"

#include "pathSearch.h"
#include "map.h"

class World
{
public:
	World();

	void handleMouseClick(int x, int y, bool first_click = false);
	void handleKeyboard(int key);

	void update();

	void draw(SDL_Window *window, SDL_Renderer *ren);

private:
	Map map;
	Solver solver;
	bool success = false, finished = false;
	bool show_steps = false;
};