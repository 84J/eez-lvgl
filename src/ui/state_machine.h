#pragma once

#include "screens.h"

enum State
{
    STATE_OFF,
    STATE_SELECTION,
    STATE_RUNNING,
    STATE_PAUSE,
    STATE_DONE
};
extern enum State state;
extern enum State prev_state;

enum Screen
{
    SCREEN_OFF,
    SCREEN_PROG,
    SCREEN_PROG_ACT,
    SCREEN_MOD,
    SCREEN_MOD_2,
    SCREEN_MOD_3,
    SCREEN_MOD_SUMMARY,
    SCREEN_SET,
    SCREEN_LANGUAGE_SET,
    SCREEN_TIME_SET,
    SCREEN_PLAY,
    SCREEN_DONE,
    SCREEN_MAX
};
extern enum Screen screen;
extern enum Screen prev_screen;

enum TouchArea
{
    TA_NONE,
    TA_UPPER_LEFT,
    TA_UPPER_LEFT_MIDDLE,
    TA_UPPER_RIGHT_MIDDLE,
    TA_UPPER_RIGHT,
    TA_MIDDLE_LEFT,
    TA_MIDDLE_LEFT_MIDDLE,
    TA_MIDDLE_RIGHT_MIDDLE,
    TA_MIDDLE_RIGHT,
    TA_BOTTOM_LEFT,
    TA_BOTTOM_LEFT_MIDDLE,
    TA_BOTTOM_RIGHT_MIDDLE,
    TA_BOTTOM_RIGHT
};

enum Program
{
    PR_1,
    PR_2,
    PR_3,
    PR_4,
    PR_5,
    PR_6,
    PR_7,
    PR_8,
    PR_9,
    PR_10,
    PR_11,
    PR_12,
    PR_MAX
};
extern enum Program program;
extern enum Program prev_program;

static const int AUTO  = INT_MAX - 1;
static const int UNDEF = INT_MAX - 2;
static const int EMPTY = INT_MAX - 3;
struct ProgramState
{
    int time;
    int temp;
    int rpm;
    int load;
};

enum Modifier
{
    MOD_NONE,

    MOD_CF1_BEGIN,
    MOD_PREWASH,
    MOD_SPEEDWASH,
    MOD_MINILOAD,
    MOD_EXTRARINSE,
    MOD_EXTRAWATER,
    MOD_CF1_END,

    MOD_CF2_BEGIN,
    MOD_TOMATO,
    MOD_CHOCO,
    MOD_GRASS,
    MOD_WINE,
    MOD_BLOOD,
    MOD_COFFEE,
    MOD_CF2_END,

    MOD_CF3_BEGIN,
    MOD_STEAM,
    MOD_CF3_END,

    MOD_MAX
};
extern enum Modifier active_modifier[3];

void state_set(enum State s);
void screen_set(enum Screen s);
void screen_set_previous(void);
void program_set(enum Program p);

void touch(enum TouchArea area);
void process_touch(enum TouchArea area);

void state_machine_update(void);


