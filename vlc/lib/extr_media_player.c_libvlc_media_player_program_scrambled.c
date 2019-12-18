#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_program {int scrambled; } ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;

/* Variables and functions */
 struct vlc_player_program* vlc_player_GetSelectedProgram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

bool libvlc_media_player_program_scrambled(libvlc_media_player_t *p_mi)
{
    bool b_program_scrambled = false;

    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    const struct vlc_player_program *program =
        vlc_player_GetSelectedProgram(player);
    if (!program)
        goto end;

    b_program_scrambled = program->scrambled;

    vlc_player_Unlock(player);
end:
    return b_program_scrambled;
}