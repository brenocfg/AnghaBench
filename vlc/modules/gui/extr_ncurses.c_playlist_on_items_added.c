#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct TYPE_2__ {int need_update; } ;
typedef  TYPE_1__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 

__attribute__((used)) static void
playlist_on_items_added(vlc_playlist_t *playlist,
                        size_t index,
                        vlc_playlist_item_t *const items[], size_t count,
                        void *userdata)
{
    VLC_UNUSED(playlist);
    VLC_UNUSED(index); VLC_UNUSED(items); VLC_UNUSED(count);

    intf_sys_t *sys = (intf_sys_t *)userdata;
    sys->need_update = true;
}