#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  httpd_host_t ;
typedef  int /*<<< orphan*/  httpd_file_t ;
struct TYPE_4__ {int /*<<< orphan*/  L; int /*<<< orphan*/  ref; int /*<<< orphan*/  password; } ;
typedef  TYPE_1__ httpd_file_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * httpd_FileNew (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
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
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  vlclua_httpd_file_callback ; 
 int /*<<< orphan*/  vlclua_httpd_file_delete ; 

__attribute__((used)) static int vlclua_httpd_file_new( lua_State *L )
{
    httpd_host_t **pp_host = (httpd_host_t **)luaL_checkudata( L, 1, "httpd_host" );
    const char *psz_url = luaL_checkstring( L, 2 );
    const char *psz_mime = luaL_nilorcheckstring( L, 3 );
    const char *psz_user = luaL_nilorcheckstring( L, 4 );
    const char *psz_password = luaL_nilorcheckstring( L, 5 );
    /* Stack item 7 is the callback function */
    luaL_argcheck( L, lua_isfunction( L, 6 ), 6, "Should be a function" );
    /* Stack item 8 is the callback data */
    httpd_file_sys_t *p_sys = (httpd_file_sys_t *)
                              malloc( sizeof( httpd_file_sys_t ) );
    if( !p_sys )
        return luaL_error( L, "Failed to allocate private buffer." );
    p_sys->L = lua_newthread( L );
    p_sys->password = psz_password && *psz_password;
    p_sys->ref = luaL_ref( L, LUA_REGISTRYINDEX ); /* pops the object too */
    lua_xmove( L, p_sys->L, 2 );
    httpd_file_t *p_file = httpd_FileNew( *pp_host, psz_url, psz_mime,
                                          psz_user, psz_password,
                                          vlclua_httpd_file_callback, p_sys );
    if( !p_file )
    {
        free( p_sys );
        return luaL_error( L, "Failed to create HTTPd file." );
    }

    httpd_file_t **pp_file = lua_newuserdata( L, sizeof( httpd_file_t * ) );
    *pp_file = p_file;

    if( luaL_newmetatable( L, "httpd_file" ) )
    {
        lua_pushcfunction( L, vlclua_httpd_file_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}