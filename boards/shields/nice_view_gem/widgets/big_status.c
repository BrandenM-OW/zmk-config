// Added for this repo (2026-10-26): the middle of the left screen shows the layer name and the Bluetooth profile in large
// type instead of nice-view-gem's WPM gauge and chart, which redrew on every keystroke and were hard to read.
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include "big_status.h"
#include "../assets/custom_fonts.h"

// The largest of the given fonts (largest first) that fits the text across the screen.
static const lv_font_t *fit(const char *text, const lv_font_t *const *fonts, int n) {
    for (int i = 0; i < n; i++) {
        lv_point_t size;
        lv_txt_get_size(&size, text, fonts[i], 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
        if (size.x <= SCREEN_WIDTH - 2) {
            return fonts[i];
        }
    }
    return fonts[n - 1];
}

void draw_big_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_dsc;

    // layer name, e.g. BASE / LOWER / BT
    char layer[10] = {};
    if (state->layer_label == NULL) {
        snprintf(layer, sizeof(layer), "L%i", state->layer_index);
    } else {
        strncpy(layer, state->layer_label, sizeof(layer) - 1);
        to_uppercase(layer);
    }
    static const lv_font_t *const layer_fonts[] = {&lv_font_montserrat_20, &lv_font_montserrat_16};
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, fit(layer, layer_fonts, 2), LV_TEXT_ALIGN_CENTER);
    lv_canvas_draw_text(canvas, 0, 4, SCREEN_WIDTH, &label_dsc, layer);

    // divider
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);
    lv_canvas_draw_rect(canvas, 10, 31, SCREEN_WIDTH - 20, 1, &rect_dsc);

    // where keys go: USB, or the Bluetooth profile (1-5, as numbered on the BT layer keys BT0-BT4 + 1)
    char link[8] = {};
    if (state->selected_endpoint.transport == ZMK_TRANSPORT_USB) {
        strcpy(link, "USB");
    } else {
        snprintf(link, sizeof(link), "BT %d", state->active_profile_index + 1);
    }
    static const lv_font_t *const link_fonts[] = {&lv_font_montserrat_28, &lv_font_montserrat_20};
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, fit(link, link_fonts, 2), LV_TEXT_ALIGN_CENTER);
    lv_canvas_draw_text(canvas, 0, 35, SCREEN_WIDTH, &label_dsc, link);
}

void draw_link_detail(lv_obj_t *canvas, const struct status_state *state) {
    const char *text;
    if (state->selected_endpoint.transport == ZMK_TRANSPORT_USB) {
        text = "WIRED";
    } else if (!state->active_profile_bonded) {
        text = "PAIRING";
    } else if (state->active_profile_connected) {
        text = "LINKED";
    } else {
        text = "SEARCHING";
    }
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_CENTER);
    lv_canvas_draw_text(canvas, 0, 8, SCREEN_WIDTH, &label_dsc, text);
}
