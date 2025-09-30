#include "state_machine.h"
#include "images.h"
#include "utils.h"
#include "udp.h"

#include <src/core/lv_obj.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/draw/lv_image_dsc.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

enum State state = STATE_OFF;
enum State prev_state = STATE_OFF;
enum Screen screen = SCREEN_OFF;
enum Screen prev_screen = SCREEN_OFF;
enum Program program = PR_1;
enum Program prev_program = PR_1;
enum Modifier active_modifier[3] = { MOD_NONE, MOD_NONE, MOD_NONE };

enum Modifier modifier_cf1[5] = { MOD_PREWASH, MOD_SPEEDWASH, MOD_MINILOAD, MOD_EXTRARINSE, MOD_EXTRAWATER               };
enum Modifier modifier_cf2[6] = { MOD_TOMATO,  MOD_CHOCO,     MOD_GRASS,    MOD_WINE,       MOD_BLOOD,     MOD_COFFEE    };
enum Modifier modifier_cf3[3] = { MOD_NONE,    MOD_STEAM,     MOD_NONE     };

bool is_relaive_time_delay = true;
int time_delay_min = 0;

struct ProgramState programState[PR_MAX] =
{
    { 75, UNDEF, UNDEF, UNDEF },
    { 75, 40,    1600,  4     },
    { 75, 40,    1200,  4     },
    { 75, 40,    1400,  4     },
    { 75, 30,    800,   2     },
    { 75, 30,    800,   2     },
    { 75, 60,    1400,  4     },
    { 75, 30,    800,   4     },
    { 75, AUTO,  AUTO,  UNDEF },
    { 75, UNDEF, UNDEF, UNDEF },
    { 75, 30,    800,   2     },
    { 75, EMPTY, 1200,  UNDEF }
};

struct ModifierData
{
    const lv_img_dsc_t* icon;
    const char* text;
};
struct ModifierData modifier_data[MOD_MAX] =
{
    { NULL,                 ""              }, // MOD_NONE
    { NULL,                 ""              }, // MOD_CF1_BEGIN
    { &img_icon_prewash,    "Pre Wash"      },
    { &img_icon_speedwash,  "Speed Perfect" },
    { &img_icon_miniload,   "Mini Load"     },
    { &img_icon_extrarinse, "Extra Rinse"   },
    { &img_icon_extrawater, "Extra Water"   },
    { NULL,                 ""              }, // MOD_CF1_END
    { NULL,                 ""              }, // MOD_CF2_BEGIN
    { &img_icon_tomato,     "Tomato"        },
    { &img_icon_choco,      "Chocolate"     },
    { &img_icon_grass,      "Grass"         },
    { &img_icon_wine,       "Wine"          },
    { &img_icon_blood,      "Blood"         },
    { &img_icon_coffee,     "Coffee"        },
    { NULL,                 ""              }, // MOD_CF2_END
    { NULL,                 ""              }, // MOD_CF3_BEGIN
    { &img_icon_steam,      "Steam"         },
    { NULL,                 ""              }, // MOD_CF3_END
};
int rinse_level = 1;

struct ModifierUI
{
    lv_obj_t* icon;
    lv_obj_t* label;
    lv_obj_t* footerIcon;
};

void udp_send_on(void)
{
    char msg[256] = { 0 };
    udp_send("L-P1,100");
    for (int i = 2; i <= PR_MAX; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-P%d,0", i);
        udp_send(msg);
    }

    udp_send("L-BK,20");
    udp_send("L-OP,20");
    udp_send("L-FV,20");
    udp_send("L-ST,20");
    udp_send("L-LK,20");
    udp_send("L-AP,20");
    udp_send("L-PL,20");

    for (int i = 1; i <= 5; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-I%d,0,0,0,20", i);
        udp_send(msg);
    }

    for (int i = 1; i <= 6; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-C%d,0,0,0,20", i);
        udp_send(msg);
    }
}

void udp_send_off(void)
{
    char msg[256] = { 0 };
    for (int i = 1; i <= PR_MAX; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-P%d,0", i);
        udp_send(msg);
    }

    udp_send("L-BK,0");
    udp_send("L-OP,0");
    udp_send("L-FV,0");
    udp_send("L-ST,0");
    udp_send("L-LK,0");
    udp_send("L-AP,20");
    udp_send("L-PL,0");

    for (int i = 1; i <= 5; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-I%d,0,0,0,0", i);
        udp_send(msg);
    }

    for (int i = 1; i <= 6; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-C%d,0,0,0,0", i);
        udp_send(msg);
    }
}

void udp_send_program(enum Program p)
{
    char msg[256] = { 0 };
    for (int i = 0; i <= PR_MAX; ++i)
    {
        memset(msg, 0, sizeof(msg));
        if ((enum Program) i == p)
        {
            snprintf(msg, sizeof(msg), "L-P%d,100", i + 1);
        }
        else
        {
            snprintf(msg, sizeof(msg), "L-P%d,20", i + 1);
        }
        udp_send(msg);
    }
}

void udp_send_play(void)
{
    char msg[256] = { 0 };
    for (int i = 1; i <= PR_MAX; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), program == (enum Program) i ? "L-P%d,20" : "L-P%d,0", i);
        udp_send(msg);
    }

    udp_send("L-BK,0");
    udp_send("L-OP,0");
    udp_send("L-FV,0");
    udp_send("L-ST,0");
    udp_send("L-LK,0");
    udp_send("L-AP,0");
    udp_send("L-PL,20");

    for (int i = 1; i <= 5; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-I%d,0,0,0,0", i);
        udp_send(msg);
    }

    for (int i = 1; i <= 6; ++i)
    {
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg), "L-C%d,0,0,0,0", i);
        udp_send(msg);
    }
}

void set_control_visible(bool visible)
{
    printf("set control visible %d\n", visible);

    lv_obj_set_flag(objects.menu_control_area,        LV_OBJ_FLAG_HIDDEN, !visible);
    lv_obj_set_flag(objects.temperature_control_area, LV_OBJ_FLAG_HIDDEN, !visible);
    lv_obj_set_flag(objects.rpm_control_area,         LV_OBJ_FLAG_HIDDEN, !visible);
}

void set_program(enum Program p)
{
    printf("set program to %d\n", p);

    static const char* AUTO_STR  = "Auto";
    static const char* UNDEF_STR = "??";
    static const char* EMPTY_STR = "--";

    char time[32];
    snprintf(time, sizeof(time), "%dh %dm", programState[p].time / 60, programState[p].time % 60);

    char temperature[32];
    if      (programState[p].temp == AUTO)  snprintf(temperature, sizeof(temperature), "%s", AUTO_STR);
    else if (programState[p].temp == UNDEF) snprintf(temperature, sizeof(temperature), "%s *C", UNDEF_STR);
    else if (programState[p].temp == EMPTY) snprintf(temperature, sizeof(temperature), "%s *C", EMPTY_STR);
    else                                    snprintf(temperature, sizeof(temperature), "%d *C", programState[p].temp);

    char rpm[32];
    if      (programState[p].rpm == AUTO)  snprintf(rpm, sizeof(rpm), "%s", AUTO_STR);
    else if (programState[p].rpm == UNDEF) snprintf(rpm, sizeof(rpm), "%s", UNDEF_STR);
    else if (programState[p].rpm == EMPTY) snprintf(rpm, sizeof(rpm), "%s", EMPTY_STR);
    else                                   snprintf(rpm, sizeof(rpm), "%d", programState[p].rpm);

    char load[32];
    if      (programState[p].load == UNDEF) snprintf(load, sizeof(load), "%skg", UNDEF_STR);
    else                                    snprintf(load, sizeof(load), "%dkg", programState[p].load);

    lv_label_set_text(objects.time_label, time);
    lv_label_set_text(objects.temperature_label,temperature);
    lv_label_set_text(objects.temperature_label_play,temperature);
    lv_label_set_text(objects.rpm_label, rpm);
    lv_label_set_text(objects.rpm_label_play, rpm);
    lv_label_set_text(objects.load_label, load);

    lv_obj_set_flag(objects.header_rinse_label, LV_OBJ_FLAG_HIDDEN, p != PR_12);
    lv_obj_set_flag(objects.header_time_label, LV_OBJ_FLAG_HIDDEN, p != PR_12);

    lv_obj_set_flag(objects.modifier_icon1, LV_OBJ_FLAG_HIDDEN, p == PR_12);
    lv_obj_set_flag(objects.modifier_icon2, LV_OBJ_FLAG_HIDDEN, p == PR_12);
    lv_obj_set_flag(objects.modifier_icon3, LV_OBJ_FLAG_HIDDEN, p == PR_12);
    lv_obj_set_flag(objects.load_label, LV_OBJ_FLAG_HIDDEN, p == PR_12);

    const lv_img_dsc_t* bg[PR_MAX] = {
        &img_bg_prog1,
        &img_bg_prog2,
        &img_bg_prog3,
        &img_bg_prog4,
        &img_bg_prog5,
        &img_bg_prog6,
        &img_bg_prog7,
        &img_bg_prog8,
        &img_bg_prog9,
        &img_bg_prog10,
        &img_bg_prog11,
        &img_bg_prog12,
    };

    lv_obj_set_style_bg_image_src(objects.scr_prog, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(objects.scr_mods, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(objects.scr_mods_summary, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(objects.scr_time_settings, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(objects.scr_settings, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(objects.scr_play, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(objects.scr_done, bg[p], LV_PART_MAIN | LV_STATE_DEFAULT);

    udp_send_program(p);
}

void change_temperature(bool up)
{
    static const int TEMP_MIN  = 30;
    static const int TEMP_MAX  = 60;
    static const int TEMP_STEP = 10;

    int temp = programState[program].temp;

    if (temp == AUTO || temp == UNDEF || temp == EMPTY)
    {
        return;
    }

    if (up)
    {
        temp += TEMP_STEP;
        if (temp > TEMP_MAX)
        {
            temp = TEMP_MIN;
        }
    }
    else
    {
        temp -= TEMP_STEP;
        if (temp < TEMP_MIN)
        {
            temp = TEMP_MAX;
        }
    }
    programState[program].temp = temp;

    set_program(program);
}

void change_rpm(bool up)
{
    static const int RPM_MIN  = 800;
    static const int RPM_MAX  = 1600;
    static const int RPM_STEP = 200;

    int rpm = programState[program].rpm;

    if (rpm == AUTO || rpm == UNDEF || rpm == EMPTY)
    {
        return;
    }

    if (up)
    {
        rpm += RPM_STEP;
        if (rpm > RPM_MAX)
        {
            rpm = RPM_MIN;
        }
    }
    else
    {
        rpm -= RPM_STEP;
        if (rpm < RPM_MIN)
        {
            rpm = RPM_MAX;
        }
    }
    programState[program].rpm = rpm;

    set_program(program);
}

bool is_selected(enum Modifier m)
{
    for (int i = 0; i < 3; ++i)
    {
        if (active_modifier[i] == m)
        {
            return true;
        }
    }

    return false;
}

void update_modifiers(void)
{
    struct ModifierUI ui[3] =
    {
        { objects.mod_icon1, objects.mod_label1, objects.selected_modifier1 },
        { objects.mod_icon2, objects.mod_label2, objects.selected_modifier2 },
        { objects.mod_icon3, objects.mod_label3, objects.selected_modifier3 },
    };

    lv_obj_t* ui_pr_screen[3] =
    {
        objects.modifier_icon1,
        objects.modifier_icon2,
        objects.modifier_icon3,
    };

    struct ModifierUI ui_summary[3] =
    {
        { objects.mod_icon_summary1, objects.mod_label_summary1, NULL },
        { objects.mod_icon_summary2, objects.mod_label_summary2, NULL },
        { objects.mod_icon_summary3, objects.mod_label_summary3, NULL },
    };

    lv_obj_t* ui_pr_screen_play[3] =
    {
        objects.mod_icon_play1,
        objects.mod_icon_play2,
        objects.mod_icon_play3,
    };

    enum Modifier* cf = modifier_cf1;
    if (screen == SCREEN_MOD_2) cf = modifier_cf2;
    if (screen == SCREEN_MOD_3) cf = modifier_cf3;

    for (int i = 0; i < 3; ++i)
    {
        if (cf[i] == MOD_EXTRARINSE)
        {
            if (is_selected(MOD_EXTRARINSE))
            {
                if      (rinse_level == 1) lv_image_set_src(ui[i].icon, &img_icon_extrarinse1);
                else if (rinse_level == 2) lv_image_set_src(ui[i].icon, &img_icon_extrarinse2);
                else if (rinse_level == 3) lv_image_set_src(ui[i].icon, &img_icon_extrarinse3);

                char rinse[32] = { 0 };
                snprintf(rinse, sizeof(rinse), "%s +%d", modifier_data[MOD_EXTRARINSE].text, rinse_level);
                lv_label_set_text(ui[i].label, rinse);
            }
            else 
            {
                lv_image_set_src(ui[i].icon, modifier_data[MOD_EXTRARINSE].icon);
                lv_label_set_text(ui[i].label, modifier_data[MOD_EXTRARINSE].text);
            }
        }
        else
        {
            lv_image_set_src(ui[i].icon, modifier_data[cf[i]].icon);
            lv_label_set_text(ui[i].label, modifier_data[cf[i]].text);
        }
        is_selected(cf[i]) ? mod_activate(ui[i].icon, ui[i].label) : mod_deactivate(ui[i].icon, ui[i].label, ui[i].footerIcon);
    }

    for (int i = 0; i < 3; ++i)
    {
        if (active_modifier[i] == MOD_NONE)
        {
            lv_obj_set_flag(ui[i].footerIcon, LV_OBJ_FLAG_HIDDEN, true);
            lv_image_set_src(ui_pr_screen[i], &img_icon_modifier);
        }
        else
        {
            const lv_image_dsc_t* icon = modifier_data[active_modifier[i]].icon;
            if (active_modifier[i] == MOD_EXTRARINSE)
            {
                if      (rinse_level == 1) icon = &img_icon_extrarinse1;
                else if (rinse_level == 2) icon = &img_icon_extrarinse2;
                else if (rinse_level == 3) icon = &img_icon_extrarinse3;
            }

            lv_image_set_src(ui[i].footerIcon, icon);
            lv_obj_set_flag(ui[i].footerIcon, LV_OBJ_FLAG_HIDDEN, false);

            lv_image_set_src(ui_pr_screen[i], icon);
            lv_image_set_src(ui_summary[i].icon, icon);
            lv_label_set_text(ui_summary[i].label, modifier_data[active_modifier[i]].text);
            lv_image_set_src(ui_pr_screen_play[i], icon);
        }
    }
}

void update_time_delay(void)
{
    time_t raw = time(NULL);
    struct tm* t = localtime(&raw);
    char buf[6];
    strftime(buf, sizeof(buf), "%H:%M", t);

    if (is_relaive_time_delay)
    {
        char time_delay[32] = { 0 };
        snprintf(time_delay, sizeof(time_delay), "%02dmin", time_delay_min);
        lv_label_set_text(objects.time_delay_label, time_delay);

        t->tm_min += time_delay_min;
        mktime(t);
        char b[6];
        strftime(b, sizeof(b), "%H:%M", t);

        char start_time[32] = { 0 };
        snprintf(start_time, sizeof(start_time), "Start in %s", b);
        lv_label_set_text(objects.time_delay_summary_label, start_time);
    }
    else
    {

    }
}

void change_time_delay(bool up)
{
    time_delay_min += up ? 10 : -10;
    if (time_delay_min < 0) time_delay_min = 0;
    if (time_delay_min > 60) time_delay_min = 60;
    update_time_delay();
}

void rotate_cf1(bool up)
{
    for (int i = 0; i < 3; ++i)
    {
        enum Modifier modifier = modifier_cf1[i];
        modifier = modifier + (up ? -1 : 1);

        if (modifier == MOD_CF1_END) modifier = MOD_CF1_BEGIN + 1;
        else if (modifier == MOD_CF1_BEGIN) modifier = MOD_CF1_END - 1;
        modifier_cf1[i] = modifier;
    }

    update_modifiers();
}

void select_cf1(int index)
{
    printf("select cf1 index %d\n", index);

    if (index > 4) return;

    int i = 0;
    bool active = false;
    for (; i < 3; ++i)
    {
        if (active_modifier[i] == modifier_cf1[index]) { active = true; break; }
        if (active_modifier[i] == MOD_NONE) break;
    }
    if (i == 3) return;

    if (active)
    {
        if (active_modifier[i] == MOD_EXTRARINSE)
        {
            if (rinse_level == 3)
            {
                rinse_level = 1;
                active_modifier[i] = MOD_NONE;
            }
            else
            {
                rinse_level++;
            }
        }
        else
        {
            active_modifier[i] = MOD_NONE;
        }
    }
    else active_modifier[i] = modifier_cf1[index];
    update_modifiers();
}

void rotate_cf2(bool up)
{
    for (int i = 0; i < 3; ++i)
    {
        enum Modifier modifier = modifier_cf2[i];
        modifier = modifier + (up ? -1 : 1);

        if (modifier == MOD_CF2_END)
        {
            modifier = MOD_CF2_BEGIN + 1;
        }
        else if (modifier == MOD_CF2_BEGIN)
        {
            modifier = MOD_CF2_END - 1;
        }

        modifier_cf2[i] = modifier;
    }

    update_modifiers();
}

void select_cf2(int index)
{
    printf("select cf2 index %d\n", index);

    if (index > 5) return;

    int mod = 0;
    bool active = false;
    for (int i = 0; i < 3; ++i)
    {
        if (active_modifier[i] == modifier_cf2[index]) { active = true; break; }
        if (active_modifier[i] != MOD_NONE) mod++;
    }
    if (mod == 3) return;

    if (active) active_modifier[mod] = MOD_NONE;
    else active_modifier[mod] = modifier_cf2[index];

    update_modifiers();
}

void rotate_cf3(bool up)
{
    for (int i = 0; i < 3; ++i)
    {
        enum Modifier modifier = modifier_cf3[i];
        modifier = modifier + (up ? -1 : 1);

        if (modifier == MOD_CF3_END)
        {
            modifier = MOD_CF3_BEGIN + 1;
        }
        else if (modifier == MOD_CF3_BEGIN)
        {
            modifier = MOD_CF3_END - 1;
        }

        modifier_cf3[i] = modifier;
    }

    update_modifiers();
}

void select_cf3(int index)
{
    printf("select cf3 index %d\n", index);

    if (index > 2) return;

    int mod = 0;
    bool active = false;
    for (int i = 0; i < 3; ++i)
    {
        if (active_modifier[i] == modifier_cf3[index]) { active = true; break; }
        if (active_modifier[i] != MOD_NONE) mod++;
    }
    if (mod == 3) return;

    if (active) active_modifier[mod] = MOD_NONE;
    else active_modifier[mod] = modifier_cf3[index];

    update_modifiers();
}

void state_set(enum State s)
{
    printf("state set to %d\n", s);

    state = s;
}

void screen_set_previous(void)
{
    switch (screen)
    {
        case SCREEN_PROG_ACT:
        case SCREEN_MOD:
        case SCREEN_MOD_2:
        case SCREEN_MOD_3:
        case SCREEN_MOD_SUMMARY:
        case SCREEN_SET:
            if (screen == SCREEN_MOD || screen == SCREEN_MOD_2 || screen == SCREEN_MOD_3)
            {
                if (screen == SCREEN_MOD_3) udp_send("L-C3,0,0,0,20");
                if (screen == SCREEN_MOD_2) udp_send("L-C2,0,0,0,20");
                udp_send_opt_exited();
            }

            screen_set(SCREEN_PROG);
            break;

        case SCREEN_TIME_SET:
            screen_set(SCREEN_PROG_ACT);
            break;

        default:
            break;
    }
}

void screen_set(enum Screen s)
{
    printf("screen set to %d\n", s);

    screen = s;
}

void program_set(enum Program p)
{
    printf("program set to %d\n", p);

    program = p;
}

void process_touch(enum TouchArea area)
{
    printf("process touch area %d\n", area);

    switch (state)
    {
        case STATE_OFF:
            state_set(STATE_SELECTION);
            break;

        case STATE_SELECTION:
            if (screen == SCREEN_PROG) screen_set(SCREEN_PROG_ACT);
            else if (screen == SCREEN_PROG_ACT)
            {
                if      (area == TA_UPPER_RIGHT)         screen_set(SCREEN_TIME_SET);
                else if (area == TA_MIDDLE_RIGHT_MIDDLE) change_temperature(false);
                else if (area == TA_MIDDLE_RIGHT)        change_temperature(true);
                else if (area == TA_BOTTOM_RIGHT_MIDDLE) change_rpm(false);
                else if (area == TA_BOTTOM_RIGHT)        change_rpm(true);
            }
            else if (screen == SCREEN_MOD)
            {
                if      (area == TA_UPPER_RIGHT)  rotate_cf1(true);
                else if (area == TA_BOTTOM_RIGHT) rotate_cf1(false);
                else if (area == TA_UPPER_LEFT  || area == TA_UPPER_LEFT_MIDDLE  || area == TA_UPPER_RIGHT_MIDDLE)  select_cf1(0);
                else if (area == TA_MIDDLE_LEFT || area == TA_MIDDLE_LEFT_MIDDLE || area == TA_MIDDLE_RIGHT_MIDDLE) select_cf1(1);
                else if (area == TA_BOTTOM_LEFT || area == TA_BOTTOM_LEFT_MIDDLE || area == TA_BOTTOM_RIGHT_MIDDLE) select_cf1(2);
            }
            else if (screen == SCREEN_MOD_2)
            {
                if      (area == TA_UPPER_RIGHT)  rotate_cf2(true);
                else if (area == TA_BOTTOM_RIGHT) rotate_cf2(false);
                else if (area == TA_UPPER_LEFT  || area == TA_UPPER_LEFT_MIDDLE  || area == TA_UPPER_RIGHT_MIDDLE)  select_cf2(0);
                else if (area == TA_MIDDLE_LEFT || area == TA_MIDDLE_LEFT_MIDDLE || area == TA_MIDDLE_RIGHT_MIDDLE) select_cf2(1);
                else if (area == TA_BOTTOM_LEFT || area == TA_BOTTOM_LEFT_MIDDLE || area == TA_BOTTOM_RIGHT_MIDDLE) select_cf2(2);
            }
            else if (screen == SCREEN_MOD_3)
            {
                if      (area == TA_UPPER_RIGHT)  rotate_cf3(true);
                else if (area == TA_BOTTOM_RIGHT) rotate_cf3(false);
                else if (area == TA_UPPER_LEFT  || area == TA_UPPER_LEFT_MIDDLE  || area == TA_UPPER_RIGHT_MIDDLE)  select_cf3(0);
                else if (area == TA_MIDDLE_LEFT || area == TA_MIDDLE_LEFT_MIDDLE || area == TA_MIDDLE_RIGHT_MIDDLE) select_cf3(1);
                else if (area == TA_BOTTOM_LEFT || area == TA_BOTTOM_LEFT_MIDDLE || area == TA_BOTTOM_RIGHT_MIDDLE) select_cf3(2);
            }
            else if (screen == SCREEN_TIME_SET)
            {
                if      (area == TA_MIDDLE_RIGHT_MIDDLE) change_time_delay(false);
                else if (area == TA_MIDDLE_RIGHT)        change_time_delay(true);
                else if (area == TA_BOTTOM_RIGHT)       { is_relaive_time_delay = !is_relaive_time_delay; update_time_delay(); }
            }
            else if (screen == SCREEN_MOD_SUMMARY)
            {
                if (area == TA_BOTTOM_LEFT || area == TA_BOTTOM_LEFT_MIDDLE || area == TA_BOTTOM_RIGHT_MIDDLE)
                {
                    screen_set(SCREEN_MOD);
                }
                else if (area == TA_BOTTOM_RIGHT)
                {
                    state_set(STATE_RUNNING);
                }
            }
            break;

        default:
            break;
    }
}

void state_machine_update(void)
{
    if (state != prev_state)
    {
        printf("state changed from %d to %d\n", prev_state, state);

        switch (state)
        {
            case STATE_OFF:
                screen = SCREEN_OFF;
                udp_send_off();
                break;

            case STATE_SELECTION:
                screen = SCREEN_PROG;
                if (prev_state == STATE_OFF) udp_send_on();
                set_control_visible(false);
                break;

            case STATE_RUNNING:
                screen_set(SCREEN_PLAY);
                udp_send_play();
                break;

            case STATE_PAUSE:
                screen_set(SCREEN_PLAY);
                break;

            default:
                break;
        }

        prev_state = state;
        update_modifiers();
    }

    if (screen != prev_screen)
    {
        printf("screen changed from %d to %d\n", prev_screen, screen);

        switch (screen)
        {
            case SCREEN_OFF:
                lv_screen_load(objects.scr_off);
                break;

            case SCREEN_PROG:
                set_control_visible(false);
                lv_obj_set_style_bg_image_opa(objects.scr_prog, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_screen_load(objects.scr_prog);
                break;

            case SCREEN_PROG_ACT:
                 set_control_visible(true);
                 lv_obj_set_style_bg_image_opa(objects.scr_prog, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
                 lv_screen_load(objects.scr_prog);
                break;

            case SCREEN_MOD:
            case SCREEN_MOD_2:
            case SCREEN_MOD_3:
                if (screen == SCREEN_MOD) udp_send_opt_entered();
                else if (screen == SCREEN_MOD_2) { udp_send("L-C2,0,0,0,100"); udp_send("L-BK,100"); }
                else if (screen == SCREEN_MOD_3) { udp_send("L-C3,0,0,0,100"); udp_send("L-BK,100"); }

                lv_screen_load(objects.scr_mods);
                update_modifiers();
                break;

            case SCREEN_MOD_SUMMARY:
                lv_screen_load(objects.scr_mods_summary);
                update_modifiers();
                break;

            case SCREEN_SET:
                lv_screen_load(objects.scr_settings);
                break;

            case SCREEN_TIME_SET:
                lv_screen_load(objects.scr_time_settings);
                update_time_delay();
                break;

            case SCREEN_PLAY:
                lv_screen_load(objects.scr_play);
                break;

            case SCREEN_DONE:
                lv_screen_load(objects.scr_done);
                break;

            default:
                // ignore
                break;
        }

        prev_screen = screen;
    }

    if (program != prev_program)
    {
        printf("program changed from %d to %d\n", prev_program, program);

        state_set(STATE_SELECTION);
        screen_set(SCREEN_PROG);
        set_control_visible(false);
        set_program(program);
    
        prev_program = program;
    }
}
