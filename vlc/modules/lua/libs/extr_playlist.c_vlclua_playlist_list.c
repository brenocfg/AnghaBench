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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  push_playlist_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_list(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    vlc_playlist_Lock(playlist);

    size_t count = vlc_playlist_Count(playlist);
    lua_createtable(L, count, 0);

    for (size_t i = 0; i < count; ++i)
    {
        push_playlist_item(L, vlc_playlist_Get(playlist, i));
        lua_rawseti(L, -2, i + 1);
    }

    vlc_playlist_Unlock(playlist);

    return 1;
}