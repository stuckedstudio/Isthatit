#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
};