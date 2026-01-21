#pragma once
#include "Graphics.h"
#include "visual/Piano.h"
#include <SDL3/SDL.h>

class Renderer
{
public:
	bool Init(SDL_Window* window);
	void Present();

	void Draw();

	SDL_Renderer* GetSDLRenderer();
	void ShutDown();
private:
	SDL_Renderer* renderer;

private:
	std::vector<std::unique_ptr<Drawable>> drawables;
};
