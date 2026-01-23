#include "Input.h"

namespace Input
{
	namespace 
	{
		int mouseX = 0;
		int mouseY = 0;
		bool leftMouseDown = false;
		bool leftMouseHold = false;
		bool rightMouseDown = false;
		bool rightMouseHold = false;

		// The callback LVGL will call internally
		void ReadCallbackMain(lv_indev_t* indev, lv_indev_data_t* data)
		{
			data->point.x = mouseX;
			data->point.y = mouseY;
			data->state = leftMouseDown ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
		}
		void ReadCallbackSecondary(lv_indev_t* indev, lv_indev_data_t* data) 
		{
			data->point.x = mouseX;
			data->point.y = mouseY;
			data->state = rightMouseDown ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
		}
	}
	void ProcessMouseInput(SDL_Event* e)
	{
		if (e->type == SDL_EVENT_MOUSE_MOTION) 
		{
			mouseX = e->motion.x;
			mouseY = e->motion.y;
		}
		else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				if (leftMouseDown)
				{
					leftMouseDown = false;
					leftMouseHold = true;
				}
				else
				{
					leftMouseDown = true;
					leftMouseHold = false;
				}
			}
			if (e->button.button == SDL_BUTTON_RIGHT)
			{
				if (rightMouseDown)
				{
					rightMouseDown = false;
					rightMouseHold = true;
				}
				else
				{
					rightMouseDown = true;
					rightMouseHold = false;
				}
			}
		}
		else if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) 
		{
			if (e->button.button == SDL_BUTTON_LEFT) 
			{
				leftMouseDown = false;
				leftMouseHold = false;
			}
			if (e->button.button == SDL_BUTTON_RIGHT) 
			{
				rightMouseDown = false;
				rightMouseHold = false;
			}
		}
	}

	void InitLVGLInput()
	{
		lv_indev_t* mouseMainIndev = lv_indev_create();
		lv_indev_set_read_cb(mouseMainIndev, Input::ReadCallbackMain);
		lv_indev_set_type(mouseMainIndev, LV_INDEV_TYPE_POINTER);

		//lv_indev_t* mouseSecondaryIndev = lv_indev_create();
		//lv_indev_set_read_cb(mouseSecondaryIndev, Input::ReadCallbackMain);
		//lv_indev_set_type(mouseSecondaryIndev, LV_INDEV_TYPE_POINTER);
	}
	int GetX() { return mouseX; }
	int GetY() { return mouseY; }
	bool IsLeftPressed() { return leftMouseDown || leftMouseHold; }
	bool IsRightPressed() { return rightMouseDown || rightMouseHold; }
	
};