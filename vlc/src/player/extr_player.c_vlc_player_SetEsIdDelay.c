#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_5__ {scalar_t__ i_cat; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_1__ fmt; } ;
struct vlc_player_track_priv {scalar_t__ delay; TYPE_2__ t; } ;
struct vlc_player_input {int /*<<< orphan*/  thread; } ;
struct TYPE_7__ {int /*<<< orphan*/  es_delay; } ;
typedef  TYPE_3__ input_control_param_t ;
typedef  enum vlc_player_whence { ____Placeholder_vlc_player_whence } vlc_player_whence ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  INPUT_CONTROL_SET_ES_DELAY ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ MS_FROM_VLC_TICK (scalar_t__) ; 
 scalar_t__ SPU_ES ; 
 int VLC_EGENERIC ; 
 int VLC_PLAYER_WHENCE_ABSOLUTE ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int input_ControlPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  on_track_delay_changed ; 
 int /*<<< orphan*/  vlc_player_SendEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 struct vlc_player_track_priv* vlc_player_input_FindTrackById (struct vlc_player_input*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
vlc_player_SetEsIdDelay(vlc_player_t *player, vlc_es_id_t *es_id,
                        vlc_tick_t delay, enum vlc_player_whence whence)
{
    bool absolute = whence == VLC_PLAYER_WHENCE_ABSOLUTE;
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (!input)
        return VLC_EGENERIC;

    struct vlc_player_track_priv *trackpriv =
        vlc_player_input_FindTrackById(input, es_id, NULL);
    if (trackpriv == NULL ||
        (trackpriv->t.fmt.i_cat != AUDIO_ES && trackpriv->t.fmt.i_cat != SPU_ES))
        return VLC_EGENERIC;

    if (absolute)
        trackpriv->delay = delay;
    else
    {
        if (trackpriv->delay == INT64_MAX)
            trackpriv->delay = 0;
        trackpriv->delay += delay;
        delay = trackpriv->delay;
    }

    const input_control_param_t param = { .es_delay = { es_id, delay } };
    int ret = input_ControlPush(input->thread, INPUT_CONTROL_SET_ES_DELAY,
                                &param);
    if (ret == VLC_SUCCESS)
    {
        if (delay != INT64_MAX)
            vlc_player_osd_Message(player, _("%s delay: %i ms"),
                                   trackpriv->t.name,
                                   (int)MS_FROM_VLC_TICK(delay));
        vlc_player_SendEvent(player, on_track_delay_changed, es_id, delay);
    }

    return VLC_SUCCESS;
}