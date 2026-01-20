#include "UI.h"

namespace UI 
{
	namespace 
	{
		std::shared_ptr<uint8_t> draw_buf = std::shared_ptr<uint8_t>(new uint8_t[DRAW_BUF_SIZE], std::default_delete<uint8_t[]>());
        SDL_Texture* uiTexture = nullptr;
        //uint8_t draw_buf[DRAW_BUF_SIZE];
	}

	void UIFlush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
	{
        SDL_Renderer* renderer = (SDL_Renderer*)lv_display_get_user_data(disp);

        // 1. Initialize the texture once if it doesn't exist
        if (!uiTexture) {
            uiTexture = SDL_CreateTexture(renderer,
                SDL_PIXELFORMAT_XRGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_SetTextureBlendMode(uiTexture, SDL_BLENDMODE_BLEND); // Allows transparency if you switch back to ARGB
        }

        // 2. Update the texture with LVGL's pixel data
        SDL_Rect rect;
        rect.x = area->x1;
        rect.y = area->y1;
        rect.w = area->x2 - area->x1 + 1;
        rect.h = area->y2 - area->y1 + 1;

        // Update the specific part of the texture that changed
        SDL_UpdateTexture(uiTexture, &rect, px_map, rect.w * 4);

        // 3. Tell LVGL we are ready
        lv_display_flush_ready(disp);
	}

    uint8_t* getDrawBuffer()
    {
		//return draw_buf;
		return draw_buf.get();
    }
    SDL_Texture* getUITexture()
    {
		return uiTexture;
    }
}
