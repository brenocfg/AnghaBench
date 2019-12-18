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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  httpd_host_t ;
typedef  int /*<<< orphan*/  httpd_handler_t ;
struct TYPE_5__ {int /*<<< orphan*/  L; int /*<<< orphan*/  password; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ httpd_handler_lua_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * httpd_HandlerNew (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 char* luaL_nilorcheckstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  vlclua_httpd_handler_callback ; 
 int /*<<< orphan*/  vlclua_httpd_handler_delete ; 

__attribute__((used)) static int vlclua_httpd_handler_new( lua_State * L )
{
    httpd_host_t **pp_host = (httpd_host_t **)luaL_checkudata( L, 1, "httpd_host" );
    const char *psz_url = luaL_checkstring( L, 2 );
    const char *psz_user = luaL_nilorcheckstring( L, 3 );
    const char *psz_password = luaL_nilorcheckstring( L, 4 );
    /* Stack item 5 is the callback function */
    luaL_argcheck( L, lua_isfunction( L, 5 ), 5, "Should be a function" );
    /* Stack item 6 is the callback data */
    lua_settop( L, 6 );
    httpd_handler_lua_t *p_sys = malloc( sizeof( *p_sys ) );
    if( !p_sys )
        return luaL_error( L, "Failed to allocate private buffer." );
    p_sys->L = lua_newthread( L );
    p_sys->ref = luaL_ref( L, LUA_REGISTRYINDEX ); /* pops the object too */
    p_sys->password = psz_password && *psz_password;
    /* use lua_xmove to move the lua callback function and data to
     * the callback's stack. */
    lua_xmove( L, p_sys->L, 2 );
    httpd_handler_t *p_handler = httpd_HandlerNew(
                            *pp_host, psz_url, psz_user, psz_password,
                            vlclua_httpd_handler_callback, p_sys );
    if( !p_handler )
    {
        free( p_sys );
        return luaL_error( L, "Failed to create HTTPd handler." );
    }

    httpd_handler_t **pp_handler = lua_newuserdata( L, sizeof( httpd_handler_t * ) );
    *pp_handler = p_handler;

    if( luaL_newmetatable( L, "httpd_handler" ) )
    {
        lua_pushcfunction( L, vlclua_httpd_handler_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}