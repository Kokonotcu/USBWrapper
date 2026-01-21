#include "Application.h"

Application::Application()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window =  SDL_CreateWindow("Cross-Platform Synth", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	renderer.Init(window);
    SDL_SetRenderVSync(renderer.GetSDLRenderer(), 1);

    audio.Init();
}

void Application::Run()
{
    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

		renderer.DrawSDL();

		Graphics::DrawUI();

		renderer.Present();
    }
}

void Application::Cleanup()
{
    renderer.ShutDown();
    SDL_DestroyWindow(window);
	SDL_Quit();
    audio.Cleanup();
}
