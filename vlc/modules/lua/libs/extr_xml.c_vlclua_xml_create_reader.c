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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_xml_reader_delete ; 
 int /*<<< orphan*/  vlclua_xml_reader_reg ; 
 int /*<<< orphan*/ * xml_ReaderCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_xml_create_reader( lua_State *L )
{
    vlc_object_t *obj = vlclua_get_this( L );
    stream_t *p_stream = *(stream_t **)luaL_checkudata( L, 2, "stream" );

    xml_reader_t *p_reader = xml_ReaderCreate( obj, p_stream );
    if( !p_reader )
        return luaL_error( L, "XML reader creation failed." );

    xml_reader_t **pp_reader = lua_newuserdata( L, sizeof( xml_reader_t * ) );
    *pp_reader = p_reader;

    if( luaL_newmetatable( L, "xml_reader" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_xml_reader_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_xml_reader_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}