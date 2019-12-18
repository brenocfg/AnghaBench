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
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_9__ {size_t size; scalar_t__* data; } ;
struct TYPE_8__ {int need_update; TYPE_3__ pl_item_names; int /*<<< orphan*/ * playlist; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 char* input_item_GetTitleFbName (int /*<<< orphan*/ *) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * vlc_playlist_item_GetMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_vector_push (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_vector_reserve (TYPE_3__*,size_t) ; 

__attribute__((used)) static void PlaylistRebuild(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;
    vlc_playlist_t *playlist = sys->playlist;

    for (size_t i = 0; i < sys->pl_item_names.size; ++i)
        free((void *)sys->pl_item_names.data[i]);
    vlc_vector_clear(&sys->pl_item_names);

    size_t count = vlc_playlist_Count(playlist);
    if (!vlc_vector_reserve(&sys->pl_item_names, count))
        return;
    for (size_t i = 0; i < count; ++i)
    {
        vlc_playlist_item_t *plitem = vlc_playlist_Get(playlist, i);
        input_item_t *item = vlc_playlist_item_GetMedia(plitem);
        char *name = input_item_GetTitleFbName(item);
        vlc_vector_push(&sys->pl_item_names, name);
    }

    sys->need_update = false;
}