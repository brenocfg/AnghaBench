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
typedef  int /*<<< orphan*/  vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** vlc_player_osd_HoldAll (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  vlc_player_osd_ReleaseAll (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  vouts_osd_Icon (int /*<<< orphan*/ **,size_t,short) ; 

void
vlc_player_osd_Icon(vlc_player_t *player, short type)
{
    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    vouts_osd_Icon(vouts, count, type);

    vlc_player_osd_ReleaseAll(player, vouts, count);
}