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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  httpd_redirect_t ;
typedef  int /*<<< orphan*/  httpd_host_t ;

/* Variables and functions */
 int /*<<< orphan*/ * httpd_RedirectNew (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_httpd_redirect_delete ; 

__attribute__((used)) static int vlclua_httpd_redirect_new( lua_State *L )
{
    httpd_host_t **pp_host = (httpd_host_t **)luaL_checkudata( L, 1, "httpd_host" );
    const char *psz_url_dst = luaL_checkstring( L, 2 );
    const char *psz_url_src = luaL_checkstring( L, 3 );
    httpd_redirect_t *p_redirect = httpd_RedirectNew( *pp_host,
                                                      psz_url_dst,
                                                      psz_url_src );
    if( !p_redirect )
        return luaL_error( L, "Failed to create HTTPd redirect." );

    httpd_redirect_t **pp_redirect = lua_newuserdata( L, sizeof( httpd_redirect_t * ) );
    *pp_redirect = p_redirect;

    if( luaL_newmetatable( L, "httpd_redirect" ) )
    {
        lua_pushcfunction( L, vlclua_httpd_redirect_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}