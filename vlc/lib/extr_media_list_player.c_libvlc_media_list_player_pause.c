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
struct TYPE_5__ {int /*<<< orphan*/  p_mi; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_player_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

void libvlc_media_list_player_pause(libvlc_media_list_player_t * p_mlp)
{
    lock(p_mlp);
    libvlc_media_player_pause(p_mlp->p_mi);
    unlock(p_mlp);
}