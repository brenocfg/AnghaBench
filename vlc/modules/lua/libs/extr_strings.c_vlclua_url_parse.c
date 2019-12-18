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
struct TYPE_4__ {int /*<<< orphan*/  psz_option; int /*<<< orphan*/  psz_path; int /*<<< orphan*/  i_port; int /*<<< orphan*/  psz_host; int /*<<< orphan*/  psz_password; int /*<<< orphan*/  psz_username; int /*<<< orphan*/  psz_protocol; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_UrlParse (TYPE_1__*,char const*) ; 

int vlclua_url_parse( lua_State *L )
{
    const char *psz_url = luaL_checkstring( L, 1 );
    vlc_url_t url;

    vlc_UrlParse( &url, psz_url );

    lua_newtable( L );
    lua_pushstring( L, url.psz_protocol );
    lua_setfield( L, -2, "protocol" );
    lua_pushstring( L, url.psz_username );
    lua_setfield( L, -2, "username" );
    lua_pushstring( L, url.psz_password );
    lua_setfield( L, -2, "password" );
    lua_pushstring( L, url.psz_host );
    lua_setfield( L, -2, "host" );
    lua_pushinteger( L, url.i_port );
    lua_setfield( L, -2, "port" );
    lua_pushstring( L, url.psz_path );
    lua_setfield( L, -2, "path" );
    lua_pushstring( L, url.psz_option );
    lua_setfield( L, -2, "option" );

    vlc_UrlClean( &url );

    return 1;
}