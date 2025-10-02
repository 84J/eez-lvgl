#include "lang.h"

enum Language language = LANG_EN;
struct LanguageMeta lang_meta[OBJ_MAX];
bool meta_init = false;

void lang_init(void)
{
    if (meta_init) return;

    lang_meta[OBJ_HEADER_RINSE_LABEL] = (struct LanguageMeta) { { "Rinse", "Spulen" }, objects.header_rinse_label };
    lang_meta[OBJ_HEADER_SUMMARY] = (struct LanguageMeta) { { "Activated", "Aktiviert" }, objects.header_summary };
    lang_meta[OBJ_LABEL_SUMMARY_EDIT] = (struct LanguageMeta) { { "Edit", "Bearbeiten" }, objects.label_summary_edit };
    lang_meta[OBJ_LABEL_TIME_START_IN] = (struct LanguageMeta) { { "Start in", "Fertig um" }, objects.mod_label_time_start };
    lang_meta[OBJ_LABEL_SETTINGS_SOUND] = (struct LanguageMeta) { { "Sound", "Ton" }, objects.setting_label1 };
    lang_meta[OBJ_LABEL_SETTINGS_DISPLAY] = (struct LanguageMeta) { { "Display", "Anzeige" }, objects.setting_label2 };
    lang_meta[OBJ_LABEL_SETTINGS_LANGUAGE] = (struct LanguageMeta) { { "Language", "Sprache" }, objects.setting_label3 };

    meta_init = true;
}

void lang_set(enum Language l)
{
    if (language == l) return;

    lang_init();

    for (int i = 0; i < OBJ_MAX; ++i)
    {
        lv_label_set_text(lang_meta[i].obj, lang_meta[i].text[l]);
    }

    language = l;
}
