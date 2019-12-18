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

/* Variables and functions */
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char const* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static const char *vlclua_sd_description( vlc_object_t *obj, lua_State *L,
                                          const char *filename )
{
    lua_getglobal( L, "descriptor" );
    if( !lua_isfunction( L, -1 ) )
    {
        msg_Warn( obj, "No 'descriptor' function in '%s'", filename );
        lua_pop( L, 1 );
        return NULL;
    }

    if( lua_pcall( L, 0, 1, 0 ) )
    {
        msg_Warn( obj, "Error while running script %s, "
                  "function descriptor(): %s", filename,
                  lua_tostring( L, -1 ) );
        lua_pop( L, 1 );
        return NULL;
    }

    lua_getfield( L, -1, "title" );
    if ( !lua_isstring( L, -1 ) )
    {
        msg_Warn( obj, "'descriptor' function in '%s' returned no title",
                  filename );
        lua_pop( L, 2 );
        return NULL;
    }

    return lua_tostring( L, -1 );
}