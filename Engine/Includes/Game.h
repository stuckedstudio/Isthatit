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


	static SDL_Renderer *renderer;
	static SDL_Window *window;
private:
	bool isRunning = false;
	int cnt = 0;
};