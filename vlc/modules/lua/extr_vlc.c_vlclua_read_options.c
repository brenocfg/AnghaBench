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
 int /*<<< orphan*/  TAB_APPEND (int,char**,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

void vlclua_read_options( vlc_object_t *p_this, lua_State *L,
                            int *pi_options, char ***pppsz_options )
{
    lua_getfield( L, -1, "options" );
    if( lua_istable( L, -1 ) )
    {
        lua_pushnil( L );
        while( lua_next( L, -2 ) )
        {
            if( lua_isstring( L, -1 ) )
            {
                char *psz_option = strdup( lua_tostring( L, -1 ) );
                msg_Dbg( p_this, "Option: %s", psz_option );
                TAB_APPEND( *pi_options, *pppsz_options, psz_option );
            }
            else
            {
                msg_Warn( p_this, "Option should be a string" );
            }
            lua_pop( L, 1 ); /* pop option */
        }
    }
    lua_pop( L, 1 ); /* pop "options" */
}