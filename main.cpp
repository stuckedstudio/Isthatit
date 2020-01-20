#include "Engine/Includes/Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

	
	
	u_int32_t frameStart;
	int frameTime;
	game = new Game();
	game->init("GameWindow", 800, 640, false);
	SDL_DisplayMode currentDisMode;
	int FPS;
	if(SDL_GetCurrentDisplayMode(0,&currentDisMode) != 0)
	{
		std::string error = "SDL error getting displaymode" + std::string(SDL_GetError());
		SDL_Log(error.c_str());
	}
	else
	{
		FPS = currentDisMode.refresh_rate;
		if(FPS == 0)
		{
			FPS = 60;
		}
	}
	
	const int frameDelay = 1000/FPS;
	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay-frameTime);
		}
	}

	game->clean();
	return 0;
}