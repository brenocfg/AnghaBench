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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int vlc_playlist_AppendOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_PlayAt (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_read_input_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_add_common(lua_State *L, bool play)
{
    vlc_object_t *obj = vlclua_get_this(L);
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    int count = 0;

    /* playlist */
    if (!lua_istable(L, -1))
    {
        msg_Warn(obj, "Playlist should be a table.");
        return 0;
    }

    lua_pushnil(L);

    vlc_playlist_Lock(playlist);

    /* playlist nil */
    while (lua_next(L, -2))
    {
        input_item_t *item = vlclua_read_input_item(obj, L);
        if (item != NULL)
        {
            int ret = vlc_playlist_AppendOne(playlist, item);
            if (ret == VLC_SUCCESS)
            {
                count++;
                if (play)
                {
                    size_t last = vlc_playlist_Count(playlist) - 1;
                    vlc_playlist_PlayAt(playlist, last);
                }
            }
            input_item_Release(item);
        }
        /* pop the value, keep the key for the next lua_next() call */
        lua_pop(L, 1);
    }
    /* playlist */

    vlc_playlist_Unlock(playlist);

    lua_pushinteger(L, count);
    return 1;
}