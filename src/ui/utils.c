#include "utils.h"
#include <src/core/lv_obj.h>
#include <src/widgets/image/lv_image.h>

void mod_activate(lv_obj_t* icon, lv_obj_t* label)
{
    if (icon)
    {
        lv_obj_set_style_recolor(icon, lv_color_hex(0xF04155), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_recolor_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    if (label)
    {
        lv_obj_set_style_recolor(label, lv_color_hex(0xF04155), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_recolor_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

void mod_deactivate(lv_obj_t* icon, lv_obj_t* label, lv_obj_t* footerIcon)
{
    if (icon)  lv_obj_set_style_recolor_opa(icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (label) lv_obj_set_style_recolor_opa(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (footerIcon) lv_obj_set_flag(footerIcon, LV_OBJ_FLAG_HIDDEN, true);
}
