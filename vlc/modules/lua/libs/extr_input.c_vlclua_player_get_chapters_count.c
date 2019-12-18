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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_title {size_t chapter_count; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,size_t) ; 
 struct vlc_player_title* vlc_player_GetSelectedTitle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_player_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_player_get_chapters_count(lua_State *L)
{
    vlc_player_t *player = vlclua_get_player_internal(L);

    vlc_player_Lock(player);
    const struct vlc_player_title *current_title =
        vlc_player_GetSelectedTitle(player);

    size_t count = current_title ? current_title->chapter_count : 0;
    vlc_player_Unlock(player);

    lua_pushinteger(L, count);
    return 1;
}