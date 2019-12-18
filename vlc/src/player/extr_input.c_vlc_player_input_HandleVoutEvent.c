#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_3__ {scalar_t__ i_cat; } ;
struct TYPE_4__ {TYPE_1__ fmt; } ;
struct vlc_player_track_priv {int /*<<< orphan*/ * vout; TYPE_2__ t; } ;
struct vlc_player_input {int /*<<< orphan*/ * player; } ;
struct vlc_input_event_vout {int action; int /*<<< orphan*/ * id; int /*<<< orphan*/ * vout; int /*<<< orphan*/  order; } ;

/* Variables and functions */
 scalar_t__ VIDEO_ES ; 
#define  VLC_INPUT_EVENT_VOUT_STARTED 129 
#define  VLC_INPUT_EVENT_VOUT_STOPPED 128 
 int /*<<< orphan*/  VLC_PLAYER_VOUT_STARTED ; 
 int /*<<< orphan*/  VLC_PLAYER_VOUT_STOPPED ; 
 int /*<<< orphan*/  VLC_VOUT_ORDER_NONE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_vout_changed ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_player_SendEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vlc_player_track_priv* vlc_player_input_FindTrackById (struct vlc_player_input*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_vout_AddCallbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_vout_DelCallbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_player_input_HandleVoutEvent(struct vlc_player_input *input,
                                 const struct vlc_input_event_vout *ev)
{
    assert(ev->vout);
    assert(ev->id);

    vlc_player_t *player = input->player;

    struct vlc_player_track_priv *trackpriv =
        vlc_player_input_FindTrackById(input, ev->id, NULL);
    if (!trackpriv)
        return;

    const bool is_video_es = trackpriv->t.fmt.i_cat == VIDEO_ES;

    switch (ev->action)
    {
        case VLC_INPUT_EVENT_VOUT_STARTED:
            trackpriv->vout = ev->vout;
            vlc_player_SendEvent(player, on_vout_changed,
                                 VLC_PLAYER_VOUT_STARTED, ev->vout,
                                 ev->order, ev->id);

            if (is_video_es)
            {
                /* Register vout callbacks after the vout list event */
                vlc_player_vout_AddCallbacks(player, ev->vout);
            }
            break;
        case VLC_INPUT_EVENT_VOUT_STOPPED:
            if (is_video_es)
            {
                /* Un-register vout callbacks before the vout list event */
                vlc_player_vout_DelCallbacks(player, ev->vout);
            }

            trackpriv->vout = NULL;
            vlc_player_SendEvent(player, on_vout_changed,
                                 VLC_PLAYER_VOUT_STOPPED, ev->vout,
                                 VLC_VOUT_ORDER_NONE, ev->id);
            break;
        default:
            vlc_assert_unreachable();
    }
}