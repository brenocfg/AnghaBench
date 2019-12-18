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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct vlc_player_input {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_UNSET_ES ; 
 int VLC_SUCCESS ; 
 int input_ControlPushEsHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Track (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
vlc_player_UnselectEsId(vlc_player_t *player, vlc_es_id_t *id)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (!input)
        return;

    int ret = input_ControlPushEsHelper(input->thread, INPUT_CONTROL_UNSET_ES,
                                        id);
    if (ret == VLC_SUCCESS)
        vlc_player_osd_Track(player, id, false);
}