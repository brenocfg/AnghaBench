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
struct vlc_playlist_sort_criterion {int /*<<< orphan*/  order; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_ORDER_ASCENDING ; 
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_ORDER_DESCENDING ; 
 int VLC_SUCCESS ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_optboolean (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Shuffle (int /*<<< orphan*/ *) ; 
 int vlc_playlist_Sort (int /*<<< orphan*/ *,struct vlc_playlist_sort_criterion*,int) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sort_key_from_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 
 int vlclua_push_ret (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_playlist_sort( lua_State *L )
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    const char *keyname = luaL_checkstring(L, 1);

    int ret;
    if (!strcmp(keyname, "random"))
    {
        /* sort randomly -> shuffle */
        vlc_playlist_Lock(playlist);
        vlc_playlist_Shuffle(playlist);
        vlc_playlist_Unlock(playlist);
        ret = VLC_SUCCESS;
    }
    else
    {
        struct vlc_playlist_sort_criterion criterion;
        if (!vlc_sort_key_from_string(keyname, &criterion.key))
            return luaL_error(L, "Invalid search key.");
        criterion.order = luaL_optboolean(L, 2, 0)
                        ? VLC_PLAYLIST_SORT_ORDER_DESCENDING
                        : VLC_PLAYLIST_SORT_ORDER_ASCENDING;

        vlc_playlist_Lock(playlist);
        ret = vlc_playlist_Sort(playlist, &criterion, 1);
        vlc_playlist_Unlock(playlist);
    }
    return vlclua_push_ret(L, ret);
}