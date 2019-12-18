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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_GetMainPlaylist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

vlc_playlist_t *
vlc_intf_GetMainPlaylist(intf_thread_t *intf)
{
    vlc_playlist_t *pl = libvlc_GetMainPlaylist(vlc_object_instance(intf));
    assert(pl);
    return pl;
}