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
 int /*<<< orphan*/  vlc_playlist_MoveOne (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 
 int vlclua_push_ret (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_playlist_move(lua_State *L)
{
    uint64_t item_id = luaL_checkinteger(L, 1);
    uint64_t target_id = luaL_checkinteger(L, 2);
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    int ret;

    vlc_playlist_Lock(playlist);
    ssize_t item_index = vlc_playlist_IndexOfId(playlist, item_id);
    ssize_t target_index = vlc_playlist_IndexOfId(playlist, target_id);
    if (item_index == -1 || target_index == -1)
        ret = -1;
    else
    {
        /* if the current item was before the target, moving it shifts the
         * target item by one */
        size_t new_index = item_index <= target_index ? target_index
                                                      : target_index + 1;
        vlc_playlist_MoveOne(playlist, item_index, new_index);
        ret = VLC_SUCCESS;
    }
    vlc_playlist_Unlock(playlist);

    return vlclua_push_ret(L, ret);
}