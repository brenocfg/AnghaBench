#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_address; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {int /*<<< orphan*/  thread; } ;
struct TYPE_6__ {int b_forced; } ;
typedef  TYPE_2__ input_item_slave_t ;
typedef  enum slave_type { ____Placeholder_slave_type } slave_type ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
#define  AUDIO_ES 131 
 int /*<<< orphan*/  INPUT_CONTROL_ADD_SLAVE ; 
 int /*<<< orphan*/  SLAVE_PRIORITY_USER ; 
#define  SLAVE_TYPE_AUDIO 130 
#define  SLAVE_TYPE_SPU 129 
#define  SPU_ES 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int input_ControlPushHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* input_item_slave_New (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subtitles_Filter (char const*) ; 
 int /*<<< orphan*/  vlc_gettext (char*) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int
vlc_player_AddAssociatedMedia(vlc_player_t *player,
                              enum es_format_category_e cat, const char *uri,
                              bool select, bool notify, bool check_ext)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input || !uri)
        return VLC_EGENERIC;

    enum slave_type type;
    switch (cat)
    {
        case AUDIO_ES:
            type = SLAVE_TYPE_AUDIO;
            break;
        case SPU_ES:
            type = SLAVE_TYPE_SPU;
            break;
        default:
            return VLC_EGENERIC;
    }

    if (check_ext && type == SLAVE_TYPE_SPU && !subtitles_Filter(uri))
        return VLC_EGENERIC;

    input_item_slave_t *slave =
        input_item_slave_New(uri, type, SLAVE_PRIORITY_USER);
    if (!slave)
        return VLC_ENOMEM;
    slave->b_forced = select;

    vlc_value_t val = { .p_address = slave };
    int ret = input_ControlPushHelper(input->thread, INPUT_CONTROL_ADD_SLAVE,
                                      &val);
    if (ret != VLC_SUCCESS)
        return ret;

    if (notify)
    {
        switch( type )
        {
            case SLAVE_TYPE_AUDIO:
                vlc_player_osd_Message(player, "%s",
                                       vlc_gettext("Audio track added"));
                break;
            case SLAVE_TYPE_SPU:
                vlc_player_osd_Message(player, "%s",
                                       vlc_gettext("Subtitle track added"));
                break;
        }
    }
    return VLC_SUCCESS;
}