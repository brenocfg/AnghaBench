#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  float vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {float length; } ;
typedef  enum vlc_player_whence { ____Placeholder_vlc_player_whence } vlc_player_whence ;

/* Variables and functions */
 int MSTRTIME_MAX_SIZE ; 
 int /*<<< orphan*/  OSD_HOR_SLIDER ; 
 int /*<<< orphan*/  SEC_FROM_VLC_TICK (float) ; 
 int VLC_PLAYER_WHENCE_RELATIVE ; 
 float VLC_TICK_INVALID ; 
 int /*<<< orphan*/  secstotimestr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_player_input_GetPos (struct vlc_player_input*) ; 
 scalar_t__ vlc_player_input_GetTime (struct vlc_player_input*) ; 
 int /*<<< orphan*/ ** vlc_player_osd_HoldAll (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  vlc_player_osd_ReleaseAll (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t) ; 
 scalar_t__ vlc_player_vout_IsFullscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vouts_osd_Message (int /*<<< orphan*/ **,size_t,char*,char*,...) ; 
 int /*<<< orphan*/  vouts_osd_Slider (int /*<<< orphan*/ **,size_t,float,int /*<<< orphan*/ ) ; 

void
vlc_player_osd_Position(vlc_player_t *player,
                        struct vlc_player_input *input, vlc_tick_t time,
                        float position, enum vlc_player_whence whence)
{
    if (input->length != VLC_TICK_INVALID)
    {
        if (time == VLC_TICK_INVALID)
            time = position * input->length;
        else
            position = time / (float) input->length;
    }

    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    if (time != VLC_TICK_INVALID)
    {
        if (whence == VLC_PLAYER_WHENCE_RELATIVE)
        {
            time += vlc_player_input_GetTime(input); /* XXX: TOCTOU */
            if (time < 0)
                time = 0;
        }

        char time_text[MSTRTIME_MAX_SIZE];
        secstotimestr(time_text, SEC_FROM_VLC_TICK(time));
        if (input->length != VLC_TICK_INVALID)
        {
            char len_text[MSTRTIME_MAX_SIZE];
            secstotimestr(len_text, SEC_FROM_VLC_TICK(input->length));
            vouts_osd_Message(vouts, count, "%s / %s", time_text, len_text);
        }
        else
            vouts_osd_Message(vouts, count, "%s", time_text);
    }

    if (vlc_player_vout_IsFullscreen(player))
    {
        if (whence == VLC_PLAYER_WHENCE_RELATIVE)
        {
            position += vlc_player_input_GetPos(input); /* XXX: TOCTOU */
            if (position < 0.f)
                position = 0.f;
        }
        vouts_osd_Slider(vouts, count, position * 100, OSD_HOR_SLIDER);
    }
    vlc_player_osd_ReleaseAll(player, vouts, count);
}