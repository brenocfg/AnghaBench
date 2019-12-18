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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  httpd_host_t ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlc_http_HostNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_httpd_host_delete ; 
 int /*<<< orphan*/  vlclua_httpd_reg ; 

__attribute__((used)) static int vlclua_httpd_tls_host_new( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    httpd_host_t *p_host = vlc_http_HostNew( p_this );
    if( !p_host )
        return luaL_error( L, "Failed to create HTTP host" );

    httpd_host_t **pp_host = lua_newuserdata( L, sizeof( httpd_host_t * ) );
    *pp_host = p_host;

    if( luaL_newmetatable( L, "httpd_host" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_httpd_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_httpd_host_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}