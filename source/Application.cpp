#include "Application.h"

Application::Application()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window =  SDL_CreateWindow("Cross-Platform Synth", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	renderer.Init(window);

    lv_init();

    // 1. Create a Display Object (800x600 matches your window)
    lv_display_t* disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);

    // 2. Give LVGL the draw buffer
    lv_display_set_buffers(disp, UI::getDrawBuffer(), NULL, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

    // 3. Set the Flush Callback (The function we wrote above)
    lv_display_set_flush_cb(disp, UI::UIFlush);

    // 4. Store your SDL Renderer inside the display so the callback can find it
    lv_display_set_user_data(disp, renderer.GetSDLRenderer());
    // ------------------------

    // NOW this will work:
    lv_obj_t* screen = lv_screen_active();

    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    // 2. Create a Button
    lv_obj_t* btn = lv_button_create(screen);
    lv_obj_set_size(btn, 150, 60);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0); // Center it

    // 3. Add a Label
    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "IT WORKS!");
    lv_obj_center(label);


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

        // --- Visualizer ---
		//renderer.SetDrawColor(30, 30, 30, 255);
		//renderer.Clear();

        


        lv_tick_inc(16.6f);

        lv_obj_invalidate(lv_screen_active());
        // 2. Let LVGL do its work
        lv_timer_handler();

        SDL_RenderTexture(renderer.GetSDLRenderer(), UI::getUITexture(), NULL, NULL);

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
