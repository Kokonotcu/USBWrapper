#include "Renderer.h"

bool Renderer::Init(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, NULL);
	return true;
}

void Renderer::Clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::Present()
{
	SDL_RenderPresent(renderer);
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::FillRectangle(const SDL_FRect* rect)
{
	SDL_RenderFillRect(renderer, rect); 
}

SDL_Renderer* Renderer::GetSDLRenderer()
{
	return renderer;
}

void Renderer::ShutDown()
{
	SDL_DestroyRenderer(renderer);
}
