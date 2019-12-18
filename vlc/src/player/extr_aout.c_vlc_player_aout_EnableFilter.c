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
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_EnableFilter (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_aout_Hold (int /*<<< orphan*/ *) ; 

int
vlc_player_aout_EnableFilter(vlc_player_t *player, const char *name, bool add)
{
    audio_output_t *aout = vlc_player_aout_Hold(player);
    if (!aout)
        return -1;
    aout_EnableFilter(aout, name, add);
    aout_Release(aout);

    return 0;
}