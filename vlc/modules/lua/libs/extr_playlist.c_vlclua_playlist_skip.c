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
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_skip(lua_State *L)
{
    int n = luaL_checkinteger( L, 1 );
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    if (n < 0) {
        for (int i = 0; i < -n; i++)
            vlc_playlist_Prev(playlist);
    } else {
        for (int i = 0; i < n; ++i)
            vlc_playlist_Next(playlist);
    }
    return 0;
}