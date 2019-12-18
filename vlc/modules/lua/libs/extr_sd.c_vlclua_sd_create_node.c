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
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 int /*<<< orphan*/  INPUT_DURATION_INDEFINITE ; 
 int /*<<< orphan*/  INPUT_ITEM_URI_NOP ; 
 int /*<<< orphan*/  ITEM_NET_UNKNOWN ; 
 int /*<<< orphan*/  ITEM_TYPE_NODE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_NewExt (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_SetArtURL (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlclua_node_reg ; 
 int /*<<< orphan*/  vlclua_sd_node_delete ; 

__attribute__((used)) static input_item_t *vlclua_sd_create_node( services_discovery_t *p_sd,
                                            lua_State *L )
{
    if( !lua_istable( L, -1 ) )
    {
        msg_Err( p_sd, "Error: argument must be table" );
        return NULL;
    }

    lua_getfield( L, -1, "title" );
    if( !lua_isstring( L, -1 ) )
    {
        msg_Err( p_sd, "Error: \"%s\" parameter is required", "title" );
        return NULL;
    }

    const char *psz_name = lua_tostring( L, -1 );
    input_item_t *p_input = input_item_NewExt( INPUT_ITEM_URI_NOP, psz_name,
                                               INPUT_DURATION_INDEFINITE,
                                               ITEM_TYPE_NODE,
                                               ITEM_NET_UNKNOWN );
    lua_pop( L, 1 );

    if( unlikely(p_input == NULL) )
        return NULL;

    lua_getfield( L, -1, "arturl" );
    if( lua_isstring( L, -1 ) && strcmp( lua_tostring( L, -1 ), "" ) )
    {
        char *psz_value = strdup( lua_tostring( L, -1 ) );
        EnsureUTF8( psz_value );
        msg_Dbg( p_sd, "ArtURL: %s", psz_value );
        /* TODO: ask for art download if not local file */
        input_item_SetArtURL( p_input, psz_value );
        free( psz_value );
    }
    lua_pop( L, 1 );

    input_item_t **udata = lua_newuserdata( L, sizeof( input_item_t * ) );
    *udata = p_input;
    if( luaL_newmetatable( L, "node" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_node_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_sd_node_delete );
        lua_setfield( L, -2, "__gc" );
    }
    lua_setmetatable( L, -2 );

    return p_input;
}