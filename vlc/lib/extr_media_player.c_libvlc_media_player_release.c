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
struct TYPE_5__ {int /*<<< orphan*/  player; int /*<<< orphan*/  i_refcount; } ;
typedef  TYPE_1__ libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_player_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 

void libvlc_media_player_release( libvlc_media_player_t *p_mi )
{
    bool destroy;

    assert( p_mi );
    vlc_player_Lock(p_mi->player);
    destroy = !--p_mi->i_refcount;
    vlc_player_Unlock(p_mi->player);

    if( destroy )
        libvlc_media_player_destroy( p_mi );
}