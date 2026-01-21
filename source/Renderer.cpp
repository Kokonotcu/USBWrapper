#include "Renderer.h"

bool Renderer::Init(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, NULL);
	Graphics::Init(renderer);

	drawables.push_back(std::make_unique<Piano>());
	drawables[0]->SetPosition(0, 200);
	
	return true;
}

void Renderer::Present()
{
	SDL_RenderPresent(renderer);
}

void Renderer::Draw()
{
    // --- Visualizer ---
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

	for (const auto& drawable : drawables)
	{
		drawable->Draw(renderer);
	}

	Graphics::DrawUI();
}

SDL_Renderer* Renderer::GetSDLRenderer()
{
	return renderer;
}

void Renderer::ShutDown()
{
	SDL_DestroyRenderer(renderer);
}
