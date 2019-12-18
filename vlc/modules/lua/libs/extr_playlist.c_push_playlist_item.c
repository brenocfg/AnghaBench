#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {char* psz_uri; scalar_t__ i_duration; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetTitleFbName (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaopen_input_item (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int secf_from_vlc_tick (scalar_t__) ; 
 int /*<<< orphan*/  vlc_playlist_item_GetId (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_playlist_item_GetMedia (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_playlist_item(lua_State *L, vlc_playlist_item_t *item)
{
    lua_newtable(L);

    lua_pushinteger(L, vlc_playlist_item_GetId(item));
    lua_setfield(L, -2, "id");

    input_item_t *media = vlc_playlist_item_GetMedia(item);

    /* Apart from nb_played, these fields unfortunately duplicate
       fields already available from the input item */
    char *name = input_item_GetTitleFbName(media);
    lua_pushstring(L, name);
    free(name);
    lua_setfield(L, -2, "name");

    lua_pushstring(L, media->psz_uri);
    lua_setfield(L, -2, "path");

    if( media->i_duration < 0 )
        lua_pushnumber(L, -1);
    else
        lua_pushnumber(L, secf_from_vlc_tick(media->i_duration));
    lua_setfield(L, -2, "duration");

    luaopen_input_item(L, media);
}