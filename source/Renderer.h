#pragma once
#include "UI.h"

class Renderer
{
public:
	bool Init(SDL_Window* window);
	void Clear();
	void Present();

	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void FillRectangle(const SDL_FRect* rect);

	SDL_Renderer* GetSDLRenderer();
	void ShutDown();
private:
	SDL_Renderer* renderer;
};
