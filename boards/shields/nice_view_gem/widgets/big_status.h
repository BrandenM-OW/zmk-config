#pragma once

#include <lvgl.h>
#include "util.h"

// Large layer name + Bluetooth profile, readable from a normal sitting distance (replaces the WPM gauge and chart).
void draw_big_status(lv_obj_t *canvas, const struct status_state *state);
// One small word under it: LINKED / SEARCHING / PAIRING / WIRED.
void draw_link_detail(lv_obj_t *canvas, const struct status_state *state);
