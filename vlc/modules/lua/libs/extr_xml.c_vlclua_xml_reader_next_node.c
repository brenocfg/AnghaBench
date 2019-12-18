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
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int vlclua_xml_reader_next_node( lua_State *L )
{
    xml_reader_t *p_reader = *(xml_reader_t**)luaL_checkudata( L, 1, "xml_reader" );
    const char *psz_name;
    int i_type = xml_ReaderNextNode( p_reader, &psz_name );
    if( i_type <= 0 )
    {
        lua_pushinteger( L, 0 );
        return 1;
    }

    lua_pushinteger( L, i_type );
    lua_pushstring( L, psz_name );
    return 2;
}