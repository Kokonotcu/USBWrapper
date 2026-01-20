#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/* ENABLE CONFIG */
#define LV_CONF_SKIP 0  /* 0 = enable this file */

/* 1. COLOR SETTINGS */
#define LV_COLOR_DEPTH 32  /* Set to 32 for modern PC/GPU rendering */

/* 2. MEMORY SETTINGS */
#define LV_MEM_CUSTOM 0    /* 0: use internal heap, 1: use malloc/free */
#define LV_MEM_SIZE (128 * 1024U) /* 128KB internal heap */

/* 3. TICK SETTINGS */
#define LV_TICK_CUSTOM 0

/* 4. ENABLE WIDGETS */
#define LV_USE_BTN 1
#define LV_USE_LABEL 1

#endif /* LV_CONF_H */