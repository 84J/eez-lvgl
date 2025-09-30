#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_on_upper_left_touched(lv_event_t * e);
extern void action_on_upper_left_middle_touched(lv_event_t * e);
extern void action_on_upper_right_middle_touched(lv_event_t * e);
extern void action_on_upper_right_touched(lv_event_t * e);
extern void action_on_middle_left_touched(lv_event_t * e);
extern void action_on_middle_left_middle_touched(lv_event_t * e);
extern void action_on_middle_right_middle_touched(lv_event_t * e);
extern void action_on_middle_right_touched(lv_event_t * e);
extern void action_on_bottom_left_touched(lv_event_t * e);
extern void action_on_bottom_left_middle_touched(lv_event_t * e);
extern void action_on_bottom_right_middle_touched(lv_event_t * e);
extern void action_on_bottom_right_touched(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/