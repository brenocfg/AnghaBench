#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {int teletext_enabled; TYPE_2__* teletext_menu; int /*<<< orphan*/ * player; } ;
struct vlc_input_event_es {int action; int /*<<< orphan*/  id; int /*<<< orphan*/  fmt; int /*<<< orphan*/  title; } ;
struct TYPE_4__ {int /*<<< orphan*/  es_id; } ;
struct TYPE_5__ {TYPE_1__ t; } ;

/* Variables and functions */
#define  VLC_INPUT_ES_ADDED 132 
#define  VLC_INPUT_ES_DELETED 131 
#define  VLC_INPUT_ES_SELECTED 130 
#define  VLC_INPUT_ES_UNSELECTED 129 
#define  VLC_INPUT_ES_UPDATED 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  on_teletext_enabled_changed ; 
 int /*<<< orphan*/  on_teletext_menu_changed ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_player_SendEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_player_track_priv_Delete (TYPE_2__*) ; 
 TYPE_2__* vlc_player_track_priv_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlc_player_input_HandleTeletextMenu(struct vlc_player_input *input,
                                    const struct vlc_input_event_es *ev)
{
    vlc_player_t *player = input->player;
    switch (ev->action)
    {
        case VLC_INPUT_ES_ADDED:
            if (input->teletext_menu)
            {
                msg_Warn(player, "Can't handle more than one teletext menu "
                         "track. Using the last one.");
                vlc_player_track_priv_Delete(input->teletext_menu);
            }
            input->teletext_menu = vlc_player_track_priv_New(ev->id, ev->title,
                                                             ev->fmt);
            if (!input->teletext_menu)
                return;

            vlc_player_SendEvent(player, on_teletext_menu_changed, true);
            break;
        case VLC_INPUT_ES_DELETED:
        {
            if (input->teletext_menu && input->teletext_menu->t.es_id == ev->id)
            {
                assert(!input->teletext_enabled);

                vlc_player_track_priv_Delete(input->teletext_menu);
                input->teletext_menu = NULL;
                vlc_player_SendEvent(player, on_teletext_menu_changed, false);
            }
            break;
        }
        case VLC_INPUT_ES_UPDATED:
            break;
        case VLC_INPUT_ES_SELECTED:
        case VLC_INPUT_ES_UNSELECTED:
            if (input->teletext_menu->t.es_id == ev->id)
            {
                input->teletext_enabled = ev->action == VLC_INPUT_ES_SELECTED;
                vlc_player_SendEvent(player, on_teletext_enabled_changed,
                                     input->teletext_enabled);
            }
            break;
        default:
            vlc_assert_unreachable();
    }
}