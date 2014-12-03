#include "SDL.h"

#include "world.h"

#include <iostream>

const int screenW = 800, screenH = 600;

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window;
	SDL_Renderer *ren;
	SDL_CreateWindowAndRenderer(screenW, screenH, SDL_WINDOW_RESIZABLE, &window, &ren);

	World world;

	bool done = false;

	bool dragging = false;
	while (!done){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				done = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				world.handleMouseClick(event.motion.x, event.motion.y, true);
				dragging = true;
				break;
			case SDL_MOUSEBUTTONUP:
				dragging = false;
				break;
			case SDL_MOUSEMOTION:
				if (dragging)
					world.handleMouseClick(event.motion.x, event.motion.y);
				break;
			case SDL_KEYDOWN:
				world.handleKeyboard(event.key.keysym.sym);
				break;
			}
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		world.update();

		world.draw(window, ren);

		SDL_RenderPresent(ren);
		SDL_Delay(1);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(ren);

	return 0;
}