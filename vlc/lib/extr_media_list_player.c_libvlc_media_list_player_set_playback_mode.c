#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_playback_mode_t ;
struct TYPE_5__ {int /*<<< orphan*/  e_playback_mode; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

void libvlc_media_list_player_set_playback_mode(
                                            libvlc_media_list_player_t * p_mlp,
                                            libvlc_playback_mode_t e_mode )
{
    lock(p_mlp);
    p_mlp->e_playback_mode = e_mode;
    unlock(p_mlp);
}