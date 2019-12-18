#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int releasing_media; int next_media_requested; int /*<<< orphan*/ * next_media; int /*<<< orphan*/ * input; scalar_t__ media; } ;
typedef  TYPE_1__ vlc_player_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * input_item_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_CancelWaitError (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_InvalidateNextMedia (TYPE_1__*) ; 
 int vlc_player_OpenNextMedia (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_destructor_AddInput (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_destructor_IsEmpty (TYPE_1__*) ; 

int
vlc_player_SetCurrentMedia(vlc_player_t *player, input_item_t *media)
{
    vlc_player_assert_locked(player);

    vlc_player_CancelWaitError(player);

    vlc_player_InvalidateNextMedia(player);

    if (media)
    {
        /* Switch to this new media when the current input is stopped */
        player->next_media = input_item_Hold(media);
        player->releasing_media = false;
        player->next_media_requested = true;
    }
    else if (player->media)
    {
        /* The current media will be set to NULL once the current input is
         * stopped */
        player->releasing_media = true;
        player->next_media_requested = false;
    }
    else
        return VLC_SUCCESS;

    if (player->input)
    {
        vlc_player_destructor_AddInput(player, player->input);
        player->input = NULL;
    }

    assert(media == player->next_media);
    if (!vlc_player_destructor_IsEmpty(player))
    {
        /* This media will be opened when the input is finally stopped */
        return VLC_SUCCESS;
    }

    /* We can switch to the next media directly */
    return vlc_player_OpenNextMedia(player);
}