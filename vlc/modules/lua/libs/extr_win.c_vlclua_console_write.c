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

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  utf8_fprintf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int vlclua_console_write( lua_State *L )
{
    if( !lua_isstring( L, 1 ) )
        return luaL_error( L, "win.console_write usage: (text)" );
    const char* psz_line = luaL_checkstring( L, 1 );
    utf8_fprintf( stdout, "%s", psz_line );
    return 0;
}