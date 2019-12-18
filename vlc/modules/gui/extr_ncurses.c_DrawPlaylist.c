#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int ssize_t ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int box_idx; TYPE_1__ pl_item_names; scalar_t__ color; scalar_t__ plidx_follow; scalar_t__ need_update; int /*<<< orphan*/ * playlist; } ;
typedef  TYPE_3__ intf_sys_t ;

/* Variables and functions */
 scalar_t__ C_DEFAULT ; 
 scalar_t__ C_PLAYLIST_1 ; 
 int /*<<< orphan*/  MainBoxWrite (TYPE_3__*,size_t,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlaylistRebuild (TYPE_2__*) ; 
 int /*<<< orphan*/  color_set (scalar_t__,int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DrawPlaylist(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;
    vlc_playlist_t *playlist = sys->playlist;

    vlc_playlist_Lock(playlist);
    ssize_t cur_idx = vlc_playlist_GetCurrentIndex(playlist);
    if (sys->need_update)
        PlaylistRebuild(intf);
    vlc_playlist_Unlock(playlist);

    if (sys->plidx_follow)
        sys->box_idx = cur_idx == -1 ? 0 : cur_idx;

    for (size_t i = 0; i < sys->pl_item_names.size; i++)
    {
        if (sys->color)
            color_set(i%3 + C_PLAYLIST_1, NULL);

        MainBoxWrite(sys, i, "%c %s",
                (ssize_t)i == cur_idx ? '>' : ' ',
                sys->pl_item_names.data[i]);

        if (sys->color)
            color_set(C_DEFAULT, NULL);
    }

    return sys->pl_item_names.size;
}