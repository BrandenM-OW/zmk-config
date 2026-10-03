// Changed from nice-view-gem v0.3.0: shows one still picture (assets/peripheral_image.c, made by
// screen/make_image.py) instead of the crystal animation. Same size and position as the crystal frames.
#include <zephyr/kernel.h>
#include "animation.h"

LV_IMG_DECLARE(peripheral_image);

void draw_animation(lv_obj_t *canvas) {
    lv_obj_t *art = lv_img_create(canvas);
    lv_img_set_src(art, &peripheral_image);
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 36, 0);
}
