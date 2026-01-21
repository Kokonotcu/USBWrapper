#include "Piano.h"

void Piano::Draw(SDL_Renderer* renderer)
{
    auto voices = Synthesizer::GetActiveVoices();
    float keyWidth = (float)SCREEN_WIDTH / 128.0f;

    for (int i = 0; i < 128; i++)
    {
        SDL_FRect keyRect = { position.x + i * keyWidth, position.y + 100, keyWidth - 1, 200 };

        // Color Logic
        bool isBlackKey = (i % 12 == 1 || i % 12 == 3 || i % 12 == 6 || i % 12 == 8 || i % 12 == 10);

        if (voices[i].active)
        {
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255); // Active = Red
        }
        else
        {
            if (isBlackKey)
                SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
            else
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        }
        SDL_RenderFillRect(renderer, &keyRect);
    }
}

void Piano::SetPosition(int x, int y)
{
	position = { x, y };
}
