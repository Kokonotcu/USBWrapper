#include "ThemeManager.h"

namespace ThemeManager
{
    // ---------------------------------------------------------
    // PRIVATE VARIABLES & FUNCTIONS (Anonymous Namespace)
    // ---------------------------------------------------------
    namespace
    {
        // ---------------------------------------------------------
        // STYLE BUCKETS
        // ---------------------------------------------------------
        lv_style_t style_btn;
        lv_style_t style_btn_pressed;
        lv_style_t style_label;
        lv_style_t style_panel;

        lv_style_t style_slider_main;  // The "Groove"
        lv_style_t style_slider_indic; // The "Fill" (Blue)
        lv_style_t style_slider_knob;  // The Handle

        lv_style_t style_switch_main;
        lv_style_t style_switch_knob;

        lv_style_t style_list_main;    // Dropdowns/Rollers
        lv_style_t style_list_selected;

        // DROPDOWN STYLES
        lv_style_t style_dd_main;  // The button part
        lv_style_t style_dd_list;     // The popup box itself
        lv_style_t style_dd_selected; // The highlighted item


        // ---------------------------------------------------------
        // PALETTE
        // ---------------------------------------------------------
        lv_color_t c_bg;
        lv_color_t c_primary;
        lv_color_t c_border;
        lv_color_t c_accent;
        lv_color_t c_text;

        // Forward Declaration
        void ApplyThemeCallback(lv_theme_t* th, lv_obj_t* obj);

        void InitStyles()
        {
            // =====================================================
            // THE PALETTE: "Electric Indigo"
            // =====================================================

            // Background: Matte Black (No tint, just darkness)
            c_bg = lv_color_hex(0x111111);

            // Primary: Dark Charcoal (Distinct from black, but very subtle)
            c_primary = lv_color_hex(0x222222);

            // Border: Iron Grey (Just bright enough to see the edges)
            c_border = lv_color_hex(0x444444);

            // Accent: Pure White (The only "brightness" in the UI)
            // Active elements will light up like a white LED.
            c_accent = lv_color_hex(0xAAAADA);

            // Text: Light Grey (Slightly dimmed to avoid eye strain compared to the accent)
            c_text = lv_color_hex(0xCCCCCC);

            // =====================================================
            // 1. BUTTONS
            // =====================================================
            lv_style_init(&style_btn);
            lv_style_set_radius(&style_btn, 6);
            lv_style_set_bg_color(&style_btn, c_primary);
            lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);

            // Accent Border (Thin and precise)
            lv_style_set_border_width(&style_btn, 1);
            lv_style_set_border_color(&style_btn, c_border);
            lv_style_set_border_opa(&style_btn, LV_OPA_50); // 50% opacity for subtle look

            // Text
            lv_style_set_text_color(&style_btn, c_text);
            lv_style_set_text_letter_space(&style_btn, 1);

            // Pressed State (The "Activation")
            lv_style_init(&style_btn_pressed);
            lv_style_set_bg_color(&style_btn_pressed, c_accent);
            lv_style_set_text_color(&style_btn_pressed, c_bg); // Black text on Purple btn
            lv_style_set_translate_y(&style_btn_pressed, 2);

            // =====================================================
            // 2. SLIDERS (Faders)
            // =====================================================
            // The Track (Hollow look)
            lv_style_init(&style_slider_main);
            lv_style_set_bg_color(&style_slider_main, c_bg);
            lv_style_set_radius(&style_slider_main, 0);
            lv_style_set_border_width(&style_slider_main, 1);
            lv_style_set_border_color(&style_slider_main, lv_color_hex(0x444444));

            // The Indicator (Fill)
            lv_style_init(&style_slider_indic);
            lv_style_set_bg_color(&style_slider_indic, c_accent);
            lv_style_set_bg_opa(&style_slider_indic, LV_OPA_COVER);
            lv_style_set_radius(&style_slider_indic, 6);

            lv_style_init(&style_slider_knob);

            // The Knob (Handle) - Make it Pop!
            lv_style_init(&style_slider_knob);
            lv_style_set_bg_color(&style_slider_knob, c_primary);
            lv_style_set_border_width(&style_slider_knob, 2);
            lv_style_set_border_color(&style_slider_knob, c_text); // White outline
            lv_style_set_bg_opa(&style_slider_knob, LV_OPA_COVER);
            lv_style_set_radius(&style_slider_knob, 6);
            lv_style_set_pad_all(&style_slider_knob, 4); // Larger handle

            // [FIX] SWITCH KNOB
            lv_style_init(&style_switch_knob);
            lv_style_set_bg_opa(&style_switch_knob, LV_OPA_COVER); // No transparency
            lv_style_set_bg_color(&style_switch_knob, lv_color_hex(0x999999)); // Solid Light Grey
            lv_style_set_radius(&style_switch_knob, 0);
            lv_style_set_pad_all(&style_switch_knob, -2); // Inset slightly


            // =====================================================
            // 3. DROPDOWN (Button)
            // =====================================================
            lv_style_init(&style_dd_main);
            lv_style_set_bg_color(&style_dd_main, c_primary);
            lv_style_set_bg_opa(&style_dd_main, LV_OPA_COVER);
            lv_style_set_border_width(&style_dd_main, 1);
            lv_style_set_border_color(&style_dd_main, c_border);
            lv_style_set_radius(&style_dd_main, 6);
            lv_style_set_pad_left(&style_dd_main, 12);
            lv_style_set_pad_right(&style_dd_main, 30);
            lv_style_set_pad_top(&style_dd_main, 10);    // [FIX] More height
            lv_style_set_pad_bottom(&style_dd_main, 10); // [FIX] More height
            lv_style_set_text_color(&style_dd_main, c_text);

            // =====================================================
            // 4. DROPDOWN (List/Popup)
            // =====================================================
            lv_style_init(&style_dd_list);
            lv_style_set_bg_color(&style_dd_list, c_primary); // Match the button
            lv_style_set_bg_opa(&style_dd_list, LV_OPA_COVER);
            lv_style_set_border_width(&style_dd_list, 1);
            lv_style_set_border_color(&style_dd_list, c_border);
            lv_style_set_border_post(&style_dd_list, true);
            lv_style_set_radius(&style_dd_list, 0);
            lv_style_set_text_color(&style_dd_list, c_text);
            lv_style_set_pad_all(&style_dd_list, 4);
            lv_style_set_text_line_space(&style_dd_list, 8);

            // The Highlighted Item in the list
            lv_style_init(&style_dd_selected);
            lv_style_set_bg_color(&style_dd_selected, c_accent);
            lv_style_set_text_color(&style_dd_selected, c_bg); // Black text on Purple
        }

        // =====================================================
        // THE HOOK
        // =====================================================
        void ApplyThemeCallback(lv_theme_t* th, lv_obj_t* obj)
        {
            // 1. BUTTONS
            if (lv_obj_check_type(obj, &lv_button_class))
            {
                lv_obj_add_style(obj, &style_btn, 0);
                lv_obj_add_style(obj, &style_btn_pressed, LV_STATE_PRESSED);
            }
            // 2. LABELS
            else if (lv_obj_check_type(obj, &lv_label_class))
            {
                lv_obj_add_style(obj, &style_label, 0);
            }
            // 3. SLIDERS
            else if (lv_obj_check_type(obj, &lv_slider_class))
            {
                lv_obj_add_style(obj, &style_slider_main, LV_PART_MAIN);
                lv_obj_add_style(obj, &style_slider_indic, LV_PART_INDICATOR);
                lv_obj_add_style(obj, &style_slider_knob, LV_PART_KNOB);
            }
            // 4. SWITCHES
            else if (lv_obj_check_type(obj, &lv_switch_class))
            {
                lv_obj_add_style(obj, &style_switch_main, LV_PART_MAIN);
                lv_obj_add_style(obj, &style_switch_knob, LV_PART_KNOB);

                // When Checked (ON), the Main part (background) turns Blue
                // We create a temporary "local style" logic or just reuse the btn_pressed style for simplicity
                // But specifically for the switch, we usually set the indicator color:
                lv_obj_set_style_bg_color(obj, c_accent, LV_PART_INDICATOR | LV_STATE_CHECKED);
            }
            // Note for Dropdowns:
            if (lv_obj_check_type(obj, &lv_dropdown_class))
            {
                lv_obj_add_style(obj, &style_btn, 0);
                lv_obj_add_style(obj, &style_btn_pressed, LV_STATE_PRESSED);

                lv_obj_add_style(obj, &style_dd_main, 0);
                lv_obj_set_style_text_color(obj, c_accent, LV_PART_INDICATOR);
            }
            else if (lv_obj_check_type(obj, &lv_dropdownlist_class))
            {
                lv_obj_add_style(obj, &style_dd_list, 0);
                // Apply the selection style
                lv_obj_add_style(obj, &style_dd_selected, LV_PART_SELECTED);

                // Hide scrollbar
                lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, LV_PART_SCROLLBAR);
            }
            // 6. GENERIC PANELS
            else if (lv_obj_check_type(obj, &lv_obj_class))
            {
                // Optional
            }
        }
    }

    // ---------------------------------------------------------
    // PUBLIC FUNCTIONS
    // ---------------------------------------------------------
    void Init()
    {
        // 1. Initialize Styles (Internal)
        InitStyles();

        // 2. Create and Hook the Theme
        lv_display_t* disp = lv_display_get_default();

        lv_theme_t* th = lv_theme_default_init(disp, c_primary, c_accent, true, lv_font_get_default());

        lv_theme_set_parent(th, NULL);
        lv_theme_set_apply_cb(th, ApplyThemeCallback); // Passes our private function

        lv_display_set_theme(disp, th);
    }

    void SetPrimaryColor(lv_color_t color)
    {
        c_primary = color;
        // Re-init style property to update live
        lv_style_set_bg_color(&style_btn, c_primary);
        lv_obj_report_style_change(&style_btn); // Notify LVGL to redraw
    }

    void SetAccentColor(lv_color_t color)
    {
        c_accent = color;
        // Re-init style property to update live
        lv_style_set_border_color(&style_panel, c_accent);
		lv_obj_report_style_change(&style_panel); // Notify LVGL to redraw
    }

    lv_color_t GetPrimaryColor() { return c_primary; }
    lv_color_t GetAccentColor() { return c_accent; }
    lv_color_t GetBackgroundColor() { return c_bg; }
    lv_color_t GetTextColor() { return c_text; }
}