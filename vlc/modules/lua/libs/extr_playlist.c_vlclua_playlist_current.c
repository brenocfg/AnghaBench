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
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int vlc_playlist_item_GetId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_current(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    vlc_playlist_Lock(playlist);
    ssize_t current = vlc_playlist_GetCurrentIndex(playlist);
    int id;
    if (current != -1) {
        vlc_playlist_item_t *item = vlc_playlist_Get(playlist, current);
        id = vlc_playlist_item_GetId(item);
    } else
        id = -1;
    vlc_playlist_Unlock(playlist);

    lua_pushinteger(L, id);
    return 1;
}