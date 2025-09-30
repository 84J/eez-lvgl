#include "actions.h"
#include "state_machine.h"

void action_on_upper_left_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_UPPER_LEFT);
}

void action_on_upper_left_middle_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_UPPER_LEFT_MIDDLE);
}

void action_on_upper_right_middle_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_UPPER_RIGHT_MIDDLE);
}

void action_on_upper_right_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_UPPER_RIGHT);
}

void action_on_middle_left_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_MIDDLE_LEFT);
}

void action_on_middle_left_middle_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_MIDDLE_LEFT_MIDDLE);
}

void action_on_middle_right_middle_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_MIDDLE_RIGHT_MIDDLE);
}

void action_on_middle_right_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_MIDDLE_RIGHT);
}

void action_on_bottom_left_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_BOTTOM_LEFT);
}

void action_on_bottom_left_middle_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_BOTTOM_LEFT_MIDDLE);
}

void action_on_bottom_right_middle_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_BOTTOM_RIGHT_MIDDLE);
}

void action_on_bottom_right_touched(lv_event_t *e)
{
    (void) e;
    process_touch(TA_BOTTOM_RIGHT);
}
