#pragma once
#include <lvgl.h>
#include <memory>

namespace ThemeManager 
{
    // Call this ONCE in Graphics::Init()
    void Init();

    // --- Color Setters (Already suggested) ---
    void SetPrimaryColor(lv_color_t color);
    void SetAccentColor(lv_color_t color);

    // --- Color Getters (NEW) ---
    // Returns the current colors so you can use them in Renderer.cpp etc.
    lv_color_t GetPrimaryColor();
    lv_color_t GetAccentColor();
    lv_color_t GetBackgroundColor();
    lv_color_t GetTextColor();
}