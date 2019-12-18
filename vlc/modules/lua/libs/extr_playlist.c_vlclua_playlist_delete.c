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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_IndexOfId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveOne (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 
 int vlclua_push_ret (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_playlist_delete(lua_State *L)
{
    uint64_t id = luaL_checkinteger(L, 1);
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    int ret;

    vlc_playlist_Lock(playlist);
    ssize_t index = vlc_playlist_IndexOfId(playlist, id);
    if (index == -1)
        ret = -1;
    else
    {
        vlc_playlist_RemoveOne(playlist, index);
        ret = VLC_SUCCESS;
    }
    vlc_playlist_Unlock(playlist);

    return vlclua_push_ret(L, ret);
}