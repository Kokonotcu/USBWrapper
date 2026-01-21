#pragma once
#include <SDL3/SDL.h>

class Drawable 
{
public:
	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual void SetPosition(int x, int y) = 0;
	virtual ~Drawable() = default;
protected:
	SDL_Point position;
};