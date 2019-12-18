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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register_namespace (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_input_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_msg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_strings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_xml (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  p_reg ; 
 scalar_t__ vlclua_add_modules_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlclua_set_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lua_State * init( vlc_object_t *p_this, input_item_t * p_item, const char *psz_filename )
{
    lua_State * L = luaL_newstate();
    if( !L )
    {
        msg_Err( p_this, "Could not create new Lua State" );
        return NULL;
    }

    vlclua_set_this( L, p_this );

    /* Load Lua libraries */
    luaL_openlibs( L ); /* XXX: Don't open all the libs? */

    luaL_register_namespace( L, "vlc", p_reg );

    luaopen_msg( L );
    luaopen_stream( L );
    luaopen_strings( L );
    luaopen_variables( L );
    luaopen_object( L );
    luaopen_xml( L );
    luaopen_input_item( L, p_item );

    if( vlclua_add_modules_path( L, psz_filename ) )
    {
        msg_Warn( p_this, "Error while setting the module search path for %s",
                  psz_filename );
        lua_close( L );
        return NULL;
    }

    return L;
}