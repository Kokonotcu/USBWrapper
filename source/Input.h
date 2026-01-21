#pragma once
#include "lvgl.h"
#include <SDL3/SDL.h>


namespace Input
{
    // Call this from Application::Run loop
    void ProcessMouseInput(SDL_Event* e);

    // Call this to register the mouse with LVGL
    void InitLVGLInput();

    // Helper functions for your own game logic (Visualizer etc.)
    int GetX();
    int GetY();
    bool IsLeftPressed();
};