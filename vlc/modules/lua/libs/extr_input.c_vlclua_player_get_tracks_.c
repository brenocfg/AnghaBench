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
struct vlc_player_track {int /*<<< orphan*/  selected; int /*<<< orphan*/  name; int /*<<< orphan*/  es_id; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_es_id_GetInputId (int /*<<< orphan*/ ) ; 
 struct vlc_player_track* vlc_player_GetTrackAt (int /*<<< orphan*/ *,int,size_t) ; 
 size_t vlc_player_GetTrackCount (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_player_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_player_get_tracks_(lua_State *L,
                                     enum es_format_category_e cat)
{
    vlc_player_t *player = vlclua_get_player_internal(L);

    vlc_player_Lock(player);

    size_t count = vlc_player_GetTrackCount(player, cat);
    lua_createtable(L, count, 0);

    for (size_t i = 0; i < count; ++i)
    {
        const struct vlc_player_track *track =
                vlc_player_GetTrackAt(player, cat, i);
        if (!track) {
            continue;
        }

        lua_newtable(L);

        lua_pushinteger(L, vlc_es_id_GetInputId(track->es_id));
        lua_setfield(L, -2, "id");

        lua_pushstring(L, track->name);
        lua_setfield(L, -2, "name");

        lua_pushboolean(L, track->selected);
        lua_setfield(L, -2, "selected");

        lua_rawseti(L, -2, i + 1);
    }

    vlc_player_Unlock(player);

    return 1;
}