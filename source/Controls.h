#pragma once
#include "lvgl.h"
#include <functional>
#include <string>
#include <vector>

class DropdownList 
{
public:
    // The Constructor: One line to rule them all
    DropdownList(lv_obj_t* parent, const char* name, const char* options, int defaultIdx,
        lv_align_t align, int x_ofs, int y_ofs, // <--- NEW ARGS
        std::function<void(int)> onChange)
    {
        // 1. Create the Container
        container = lv_obj_create(parent);
        lv_obj_remove_flag(container, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_bg_opa(container, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(container, 0, 0);
        lv_obj_set_size(container, 150, 80);

        // [!!!] CRITICAL: This only works if 'parent' has NO Flex Layout [!!!]
        lv_obj_align(container, align, x_ofs, y_ofs);

        // Internal Layout: Stack Label and Dropdown vertically
        lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        // 2. Label
        label = lv_label_create(container);
        lv_label_set_text(label, name);

        // 3. Dropdown
        dd = lv_dropdown_create(container);
        lv_dropdown_set_options(dd, options);
        lv_dropdown_set_selected(dd, defaultIdx);
        lv_obj_set_width(dd, 130);

        // 4. Events
        callback = onChange;
        lv_obj_add_event_cb(dd, InternalHandler, LV_EVENT_VALUE_CHANGED, this);
    }

private:
    lv_obj_t* container;
    lv_obj_t* dd;
    lv_obj_t* label;
    std::function<void(int)> callback;

    // The "Trampoline" function: Jumps from C (LVGL) to C++ (Your Lambda)
    static void InternalHandler(lv_event_t* e)
    {
        DropdownList* self = (DropdownList*)lv_event_get_user_data(e);

        if (self && self->callback) {
            // Get the integer index (0, 1, 2...)
            int index = lv_dropdown_get_selected(self->dd);

            // Call the lambda function
            self->callback(index);
        }
    }
};