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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * vlc_stream_FilterNew (int /*<<< orphan*/ *,char const*) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_stream_add_filter( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );

    /* Make sure that we have 1 argument (+ 1 object) */
    lua_settop( L, 2 );

    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    if( !*pp_stream ) return vlclua_error( L );
    const char *psz_filter = NULL;

    if( lua_isstring( L, 2 ) )
        psz_filter = lua_tostring( L, 2 );

    if( !psz_filter || !*psz_filter )
    {
        msg_Dbg( p_this, "adding all automatic stream filters" );
        while( true )
        {
            /* Add next automatic stream */
            stream_t *p_filtered = vlc_stream_FilterNew( *pp_stream, NULL );
            if( !p_filtered )
                break;
            else
            {
                msg_Dbg( p_this, "inserted an automatic stream filter" );
                *pp_stream = p_filtered;
            }
        }
        luaL_getmetatable( L, "stream" );
        lua_setmetatable( L, 1 );
    }
    else
    {
        /* Add a named filter */
        stream_t *p_filter = vlc_stream_FilterNew( *pp_stream, psz_filter );
        if( !p_filter )
            msg_Dbg( p_this, "Unable to open requested stream filter '%s'",
                     psz_filter );
        else
        {
            *pp_stream = p_filter;
            luaL_getmetatable( L, "stream" );
            lua_setmetatable( L, 1 );
        }
    }

    return 1;
}