#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_6__ {int /*<<< orphan*/  psz_filename; int /*<<< orphan*/ * L; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int DoSearch( services_discovery_t *p_sd, const char *psz_query )
{
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    lua_State *L = p_sys->L;

    /* Lookup for the 'search' function */
    lua_getglobal( L, "search" );
    if( !lua_isfunction( L, lua_gettop( L ) ) )
    {
        msg_Err( p_sd, "The script '%s' does not define any 'search' function",
                 p_sys->psz_filename );
        lua_pop( L, 1 );
        return VLC_EGENERIC;
    }

    /* Push the query */
    lua_pushstring( L, psz_query );

    /* Call the 'search' function */
    if( lua_pcall( L, 1, 0, 0 ) )
    {
        msg_Err( p_sd, "Error while running the script '%s': %s",
                 p_sys->psz_filename, lua_tostring( L, lua_gettop( L ) ) );
        lua_pop( L, 1 );
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}