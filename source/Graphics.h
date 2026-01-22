#pragma once
#include "visual/ThemeManager.h"
#include <memory>
#include <SDL3/SDL.h>

// Screen Settings
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
#define DRAW_BUF_SIZE ( SCREEN_WIDTH* SCREEN_HEIGHT * sizeof(lv_color_t))

namespace Graphics
{
	void Init(SDL_Renderer* renderer);
	void UIFlush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map);
	void DrawUI();

	uint8_t* getDrawBuffer();
	SDL_Texture* getUITexture();
};