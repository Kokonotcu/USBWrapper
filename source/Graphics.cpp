#include "Graphics.h"

namespace Graphics 
{
	namespace 
	{
		std::shared_ptr<uint8_t> draw_buf = std::shared_ptr<uint8_t>(new uint8_t[DRAW_BUF_SIZE], std::default_delete<uint8_t[]>());
        SDL_Texture* uiTexture = nullptr;
        SDL_Renderer* renderer;
	}

    void Init(SDL_Renderer* _renderer)
    {
		renderer = _renderer;

        lv_init();

        // 1. Create a Display Object (800x600 matches your window)
        lv_display_t* disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);

        lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);

        // 2. Give LVGL the draw buffer
        lv_display_set_buffers(disp, Graphics::getDrawBuffer(), NULL, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

        // 3. Set the Flush Callback (The function we wrote above)
        lv_display_set_flush_cb(disp, Graphics::UIFlush);

        // 4. Store your SDL Renderer inside the display so the callback can find it
        lv_display_set_user_data(disp, renderer);
        // ------------------------

        // NOW this will work:
        lv_obj_t* screen = lv_screen_active();

        lv_obj_set_style_bg_opa(screen, LV_OPA_TRANSP, 0);

        lv_obj_t* drp = lv_dropdown_create(screen);
		lv_obj_set_size(drp, 150, 30);
		lv_obj_align(drp, LV_ALIGN_TOP_RIGHT, -15, 20);
		lv_obj_set_style_bg_color(drp, lv_color_make(50,120,15), 0);
        lv_obj_set_style_border_color(drp,lv_color_white(),0);

        // 2. Create a Button
        lv_obj_t* btn = lv_button_create(screen);
        lv_obj_set_size(btn, 150, 30);
        lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0); // Center it
        
        // 3. Add a Label
        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, "IT WORKS!");
        lv_obj_center(label);
	}

	void UIFlush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
	{
        SDL_Renderer* renderer = (SDL_Renderer*)lv_display_get_user_data(disp);

        // 1. Initialize the texture once if it doesn't exist
        if (!uiTexture) {
            uiTexture = SDL_CreateTexture(renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_SetTextureBlendMode(uiTexture, SDL_BLENDMODE_BLEND); // Allows transparency if you switch back to ARGB

            // OPTIONAL: Clear the texture to transparent (0x00) immediately
            void* pixels;
            int pitch;
            SDL_LockTexture(uiTexture, NULL, &pixels, &pitch);
            memset(pixels, 0, pitch * SCREEN_HEIGHT); // Set all bytes to 0 (Transparent)
            SDL_UnlockTexture(uiTexture);
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

    void DrawUI()
    {
        lv_tick_inc(16.6f);

        lv_timer_handler();

        SDL_RenderTexture(renderer, uiTexture, NULL, NULL);
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
