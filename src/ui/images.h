#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_icon_time;
extern const lv_img_dsc_t img_icon_temp;
extern const lv_img_dsc_t img_icon_rpm;
extern const lv_img_dsc_t img_icon_arrow_right;
extern const lv_img_dsc_t img_icon_minus;
extern const lv_img_dsc_t img_icon_plus;
extern const lv_img_dsc_t img_icon_modifier;
extern const lv_img_dsc_t img_icon_prewash;
extern const lv_img_dsc_t img_icon_speedwash;
extern const lv_img_dsc_t img_icon_miniload;
extern const lv_img_dsc_t img_icon_extrarinse;
extern const lv_img_dsc_t img_icon_extrawater;
extern const lv_img_dsc_t img_icon_tomato;
extern const lv_img_dsc_t img_icon_choco;
extern const lv_img_dsc_t img_icon_grass;
extern const lv_img_dsc_t img_icon_wine;
extern const lv_img_dsc_t img_icon_blood;
extern const lv_img_dsc_t img_icon_coffee;
extern const lv_img_dsc_t img_icon_steam;
extern const lv_img_dsc_t img_icon_arrow_up;
extern const lv_img_dsc_t img_icon_arrow_down;
extern const lv_img_dsc_t img_icon_sound;
extern const lv_img_dsc_t img_icon_display;
extern const lv_img_dsc_t img_icon_language;
extern const lv_img_dsc_t img_icon_plus_circle;
extern const lv_img_dsc_t img_icon_minus_circle;
extern const lv_img_dsc_t img_icon_refresh;
extern const lv_img_dsc_t img_icon_edit;
extern const lv_img_dsc_t img_icon_play;
extern const lv_img_dsc_t img_icon_ready;
extern const lv_img_dsc_t img_bg_prog1;
extern const lv_img_dsc_t img_bg_prog2;
extern const lv_img_dsc_t img_bg_prog3;
extern const lv_img_dsc_t img_bg_prog4;
extern const lv_img_dsc_t img_bg_prog5;
extern const lv_img_dsc_t img_bg_prog6;
extern const lv_img_dsc_t img_bg_prog7;
extern const lv_img_dsc_t img_bg_prog8;
extern const lv_img_dsc_t img_bg_prog9;
extern const lv_img_dsc_t img_bg_prog10;
extern const lv_img_dsc_t img_bg_prog11;
extern const lv_img_dsc_t img_bg_prog12;
extern const lv_img_dsc_t img_icon_extrarinse1;
extern const lv_img_dsc_t img_icon_extrarinse2;
extern const lv_img_dsc_t img_icon_extrarinse3;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[45];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/