#ifndef LANG_H
#define LANG_H

#include "screens.h"

enum Language
{
    LANG_EN,
    LANG_DE,
    LANG_MAX
};
extern enum Language language;

enum Object
{
    OBJ_HEADER_RINSE_LABEL,
    OBJ_HEADER_SUMMARY,
    OBJ_LABEL_SUMMARY_EDIT,
    OBJ_LABEL_TIME_START_IN,
    OBJ_LABEL_SETTINGS_SOUND,
    OBJ_LABEL_SETTINGS_DISPLAY,
    OBJ_LABEL_SETTINGS_LANGUAGE,
    OBJ_MAX
};

struct LanguageMeta
{
    const char* text[LANG_MAX];
    lv_obj_t*   obj;
};

void lang_set(enum Language l);

#endif
