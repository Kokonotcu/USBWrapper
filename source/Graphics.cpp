#include "Graphics.h"
#include "Controls.h"
#include "Synthesizer.h"

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

        lv_obj_t* screen = lv_screen_active();

        lv_obj_set_style_bg_opa(screen, LV_OPA_TRANSP, 0);

		ThemeManager::Init();

        // Create a horizontal panel to hold our controls
        lv_obj_t* mainPanel = lv_obj_create(lv_screen_active());
        lv_obj_set_size(mainPanel, 1000, 200);
        lv_obj_set_flex_flow(mainPanel, LV_FLEX_FLOW_ROW); // Items arrange left-to-right
		lv_obj_align(mainPanel, LV_ALIGN_TOP_MID, 0, 15);
        //lv_obj_center(mainPanel);

        // ---------------------------------------------------------
        // 1. OSCILLATOR WAVEFORM
        // ---------------------------------------------------------
        new DropdownList(mainPanel, "Oscillator 1", "Sine\nTriangle\nSquare\nSawtooth\nNoise", 0, LV_ALIGN_TOP_MID, 0, 150,
            [](int selectedIndex) {
                switch (selectedIndex)
                {
                        case 0:
                            Synthesizer::GetOscillator(0)->SetWaveform(std::make_unique<SineWave>());
					        break;
                        case 1:
                            Synthesizer::GetOscillator(0)->SetWaveform(std::make_unique<TriangleWave>());
						    break;
                        case 2:
							Synthesizer::GetOscillator(0)->SetWaveform(std::make_unique<SquareWave>());
							break;
						case 3:
							Synthesizer::GetOscillator(0)->SetWaveform(std::make_unique<SawtoothWave>());
							break;
						case 4:
							Synthesizer::GetOscillator(0)->SetWaveform(std::make_unique<NoiseWave>());
							break;

                        default:
                            break;
                }
            });

        // ---------------------------------------------------------
        // 2. FILTER TYPE
        // ---------------------------------------------------------
        //DropdownList(mainPanel, "FILTER", "Lowpass\nHighpass\nBandpass\nNotch", 0,
        //    [](int selectedIndex) {
        //        synth->SetFilterType(selectedIndex);
        //    });
        //
        //// ---------------------------------------------------------
        //// 3. LFO TARGET
        //// ---------------------------------------------------------
        //DropdownList(mainPanel, "LFO TARGET", "None\nPitch\nCutoff\nVolume", 2,
        //    [](int selectedIndex) {
        //        synth->SetLfoTarget(selectedIndex);
        //    });
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
