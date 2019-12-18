#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int started; TYPE_3__* input; scalar_t__ start_paused; int /*<<< orphan*/  media; scalar_t__ next_media; } ;
typedef  TYPE_1__ vlc_player_t ;
struct TYPE_11__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_PLAY_ICON ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_BOOL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vlc_player_CancelWaitError (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_destructor_IsEmpty (TYPE_1__*) ; 
 TYPE_3__* vlc_player_input_New (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int vlc_player_input_Start (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_player_osd_Icon (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
vlc_player_Start(vlc_player_t *player)
{
    vlc_player_assert_locked(player);

    vlc_player_CancelWaitError(player);

    if (player->started)
        return VLC_SUCCESS;

    if (!vlc_player_destructor_IsEmpty(player))
    {
        if (player->next_media)
        {
            player->started = true;
            return VLC_SUCCESS;
        }
        else
            return VLC_EGENERIC;
    }

    if (!player->media)
        return VLC_EGENERIC;

    if (!player->input)
    {
        /* Possible if the player was stopped by the user */
        player->input = vlc_player_input_New(player, player->media);

        if (!player->input)
            return VLC_ENOMEM;
    }
    assert(!player->input->started);

    if (player->start_paused)
    {
        var_Create(player->input->thread, "start-paused", VLC_VAR_BOOL);
        var_SetBool(player->input->thread, "start-paused", true);
    }

    int ret = vlc_player_input_Start(player->input);
    if (ret == VLC_SUCCESS)
    {
        player->started = true;
        vlc_player_osd_Icon(player, OSD_PLAY_ICON);
    }
    return ret;
}