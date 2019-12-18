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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 char* vlc_xml_encode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_convert_xml_special_chars( lua_State *L )
{
    int i_top = lua_gettop( L );
    int i;
    for( i = 1; i <= i_top; i++ )
    {
        char *psz_string = vlc_xml_encode( luaL_checkstring(L,1) );
        lua_remove( L, 1 );
        lua_pushstring( L, psz_string );
        free( psz_string );
    }
    return i_top;
}