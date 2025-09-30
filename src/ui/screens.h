#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *scr_off;
    lv_obj_t *scr_prog;
    lv_obj_t *scr_mods;
    lv_obj_t *scr_mods_summary;
    lv_obj_t *scr_time_settings;
    lv_obj_t *scr_settings;
    lv_obj_t *scr_play;
    lv_obj_t *scr_done;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *header_rinse_label;
    lv_obj_t *header_time_label;
    lv_obj_t *obj2;
    lv_obj_t *time_label;
    lv_obj_t *menu_control_area;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *temperature_label;
    lv_obj_t *temperature_control_area;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *rpm_label;
    lv_obj_t *rpm_control_area;
    lv_obj_t *obj8;
    lv_obj_t *modifier_icon1;
    lv_obj_t *modifier_icon2;
    lv_obj_t *modifier_icon3;
    lv_obj_t *load_label;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *header_wash_label_4;
    lv_obj_t *header_time_label_4;
    lv_obj_t *obj11;
    lv_obj_t *mod_icon1;
    lv_obj_t *mod_label1;
    lv_obj_t *menu_control_area_up_4;
    lv_obj_t *obj12;
    lv_obj_t *mod_icon2;
    lv_obj_t *mod_label2;
    lv_obj_t *obj13;
    lv_obj_t *mod_icon3;
    lv_obj_t *mod_label3;
    lv_obj_t *menu_control_area_down_3;
    lv_obj_t *obj14;
    lv_obj_t *selected_modifier1;
    lv_obj_t *selected_modifier2;
    lv_obj_t *selected_modifier3;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *header_summary;
    lv_obj_t *obj17;
    lv_obj_t *mod_icon_summary1;
    lv_obj_t *mod_label_summary1;
    lv_obj_t *obj18;
    lv_obj_t *mod_icon_summary2;
    lv_obj_t *mod_label_summary2;
    lv_obj_t *obj19;
    lv_obj_t *mod_icon_summary3;
    lv_obj_t *mod_label_summary3;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *header_wash_label_3;
    lv_obj_t *header_time_label_3;
    lv_obj_t *obj24;
    lv_obj_t *mod_label1_1;
    lv_obj_t *menu_control_area_up_2;
    lv_obj_t *obj25;
    lv_obj_t *time_delay_label;
    lv_obj_t *menu_control_area_up_3;
    lv_obj_t *obj26;
    lv_obj_t *time_delay_summary_label;
    lv_obj_t *menu_control_area_down_2;
    lv_obj_t *obj27;
    lv_obj_t *selected_modifier1_2;
    lv_obj_t *selected_modifier2_2;
    lv_obj_t *selected_modifier3_2;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *header_wash_label_2;
    lv_obj_t *header_time_label_2;
    lv_obj_t *obj30;
    lv_obj_t *setting_icon1;
    lv_obj_t *setting_label1;
    lv_obj_t *menu_control_area_up_1;
    lv_obj_t *obj31;
    lv_obj_t *setting_icon2;
    lv_obj_t *setting_label2;
    lv_obj_t *obj32;
    lv_obj_t *setting_icon3;
    lv_obj_t *setting_label3;
    lv_obj_t *menu_control_area_down_1;
    lv_obj_t *obj33;
    lv_obj_t *selected_modifier1_1;
    lv_obj_t *selected_modifier2_1;
    lv_obj_t *selected_modifier3_1;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *header_wash_label_5;
    lv_obj_t *header_time_label_5;
    lv_obj_t *obj36;
    lv_obj_t *mod_label1_2;
    lv_obj_t *menu_control_area_up_5;
    lv_obj_t *obj37;
    lv_obj_t *mod_label2_2;
    lv_obj_t *obj38;
    lv_obj_t *mod_icon3_1;
    lv_obj_t *temperature_label_play;
    lv_obj_t *mod_icon3_2;
    lv_obj_t *rpm_label_play;
    lv_obj_t *mod_icon_play1;
    lv_obj_t *mod_icon_play2;
    lv_obj_t *mod_icon_play3;
    lv_obj_t *obj39;
    lv_obj_t *selected_modifier1_3;
    lv_obj_t *selected_modifier2_3;
    lv_obj_t *selected_modifier3_3;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *header_wash_label_6;
    lv_obj_t *header_time_label_6;
    lv_obj_t *obj42;
    lv_obj_t *mod_label1_3;
    lv_obj_t *menu_control_area_up_6;
    lv_obj_t *obj43;
    lv_obj_t *mod_label2_3;
    lv_obj_t *obj44;
    lv_obj_t *mod_icon3_6;
    lv_obj_t *mod_label3_4;
    lv_obj_t *mod_icon3_7;
    lv_obj_t *mod_label3_5;
    lv_obj_t *mod_icon3_8;
    lv_obj_t *mod_icon3_9;
    lv_obj_t *mod_icon3_10;
    lv_obj_t *obj45;
    lv_obj_t *selected_modifier1_4;
    lv_obj_t *selected_modifier2_4;
    lv_obj_t *selected_modifier3_4;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SCR_OFF = 1,
    SCREEN_ID_SCR_PROG = 2,
    SCREEN_ID_SCR_MODS = 3,
    SCREEN_ID_SCR_MODS_SUMMARY = 4,
    SCREEN_ID_SCR_TIME_SETTINGS = 5,
    SCREEN_ID_SCR_SETTINGS = 6,
    SCREEN_ID_SCR_PLAY = 7,
    SCREEN_ID_SCR_DONE = 8,
};

void create_screen_scr_off();
void tick_screen_scr_off();

void create_screen_scr_prog();
void tick_screen_scr_prog();

void create_screen_scr_mods();
void tick_screen_scr_mods();

void create_screen_scr_mods_summary();
void tick_screen_scr_mods_summary();

void create_screen_scr_time_settings();
void tick_screen_scr_time_settings();

void create_screen_scr_settings();
void tick_screen_scr_settings();

void create_screen_scr_play();
void tick_screen_scr_play();

void create_screen_scr_done();
void tick_screen_scr_done();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/