#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

#define LV_CONF_SKIP 0

/* v9 COLOR SETTINGS - Now runtime configurable, but defaults help */
#define LV_COLOR_DEPTH 32
#define LV_COLOR_CHROMA_KEY lv_color_hex(0x00ff00)

/* MEMORY */
#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (256 * 1024U) /* 256KB */

/* TICK */
#define LV_TICK_CUSTOM 0

/* WIDGETS */
#define LV_USE_BUTTON 1  /* Renamed from LV_USE_BTN */
#define LV_USE_LABEL 1

#endif