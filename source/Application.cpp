#include "Application.h"

// Screen Settings
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Application::Application()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window =  SDL_CreateWindow("Cross-Platform Synth", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	renderer.Init(window);
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

        // --- Visualizer ---
		renderer.SetDrawColor(30, 30, 30, 255);
		renderer.Clear();

        auto voices = Synthesizer::GetActiveVoices();
        float keyWidth = (float)SCREEN_WIDTH / 128.0f;

        for (int i = 0; i < 128; i++)
        {
            SDL_FRect keyRect = { i * keyWidth, 100, keyWidth - 1, 200 };

            // Color Logic
            bool isBlackKey = (i % 12 == 1 || i % 12 == 3 || i % 12 == 6 || i % 12 == 8 || i % 12 == 10);

            if (voices[i].active)
            {
				renderer.SetDrawColor(255, 50, 50, 255); // Active = Red
            }
            else
            {
                if (isBlackKey)
					renderer.SetDrawColor(60, 60, 60, 255);
                else
					renderer.SetDrawColor(200, 200, 200, 255);
            }
			renderer.FillRectangle(&keyRect);
        }
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
