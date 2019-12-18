#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_9__ {scalar_t__ color; int /*<<< orphan*/  playlist; } ;
typedef  TYPE_2__ intf_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_meta; } ;
typedef  TYPE_3__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_CATEGORY ; 
 int /*<<< orphan*/  C_DEFAULT ; 
 int /*<<< orphan*/  MainBoxWrite (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int VLC_META_TYPE_COUNT ; 
 int /*<<< orphan*/  color_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_Release (TYPE_3__*) ; 
 char* vlc_meta_Get (int /*<<< orphan*/ ,int) ; 
 char const* vlc_meta_TypeToLocalizedString (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* vlc_player_HoldCurrentMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DrawMeta(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;
    int l = 0;

    vlc_player_t *player = vlc_playlist_GetPlayer(sys->playlist);
    vlc_player_Lock(player);
    input_item_t *item = vlc_player_HoldCurrentMedia(player);
    vlc_player_Unlock(player);
    if (!item)
        return 0;

    vlc_mutex_lock(&item->lock);
    for (int i=0; i<VLC_META_TYPE_COUNT; i++) {
        const char *meta = vlc_meta_Get(item->p_meta, i);
        if (!meta || !*meta)
            continue;

        if (sys->color) color_set(C_CATEGORY, NULL);
        MainBoxWrite(sys, l++, "  [%s]", vlc_meta_TypeToLocalizedString(i));
        if (sys->color) color_set(C_DEFAULT, NULL);
        MainBoxWrite(sys, l++, "      %s", meta);
    }
    vlc_mutex_unlock(&item->lock);

    input_item_Release(item);

    return l;
}