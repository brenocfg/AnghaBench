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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  free (char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_AddAssociatedMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,int) ; 
 int /*<<< orphan*/ * vlclua_get_player_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_input_add_subtitle(lua_State *L, bool b_path)
{
    vlc_player_t *player = vlclua_get_player_internal(L);

    if (!lua_isstring(L, 1))
        return luaL_error( L, "vlc.player.add_subtitle() usage: (path, autoselect=false)" );

    bool autoselect = false;
    if (lua_gettop(L) >= 2)
        autoselect = lua_toboolean(L, 2);

    const char *sub = luaL_checkstring(L, 1);
    char *mrl;
    if (b_path)
        mrl = vlc_path2uri(sub, NULL);

    const char *uri = b_path ? mrl : sub;
    vlc_player_AddAssociatedMedia(player, SPU_ES, uri, autoselect, true, false);
    if (b_path)
        free(mrl);

    return 1;
}