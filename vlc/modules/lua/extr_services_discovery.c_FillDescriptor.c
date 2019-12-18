#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_10__ {char const* psz_filename; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
struct TYPE_11__ {int i_capabilities; void* psz_url; void* psz_icon_url; void* psz_short_desc; } ;
typedef  TYPE_3__ services_discovery_descriptor_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 void* luaL_strdupornull (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char const* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char const*,char const*) ; 
 char** ppsz_capabilities ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ vlclua_dofile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int FillDescriptor( services_discovery_t *p_sd,
                           services_discovery_descriptor_t *p_desc )
{
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    int i_ret = VLC_EGENERIC;

    /* Create a new lua thread */
    lua_State *L = luaL_newstate();

    if( vlclua_dofile( VLC_OBJECT(p_sd), L, p_sys->psz_filename ) )
    {
        msg_Err( p_sd, "Error loading script %s: %s", p_sys->psz_filename,
                 lua_tostring( L, -1 ) );
        goto end;
    }

    /* Call the "descriptor" function */
    lua_getglobal( L, "descriptor" );
    if( !lua_isfunction( L, -1 ) || lua_pcall( L, 0, 1, 0 ) )
    {
        msg_Warn( p_sd, "Error getting the descriptor in '%s': %s",
                  p_sys->psz_filename, lua_tostring( L, -1 ) );
        goto end;
    }

    /* Get the different fields of the returned table */
    lua_getfield( L, -1, "short_description" );
    p_desc->psz_short_desc = luaL_strdupornull( L, -1 );
    lua_pop( L, 1 );

    lua_getfield( L, -1, "icon" );
    p_desc->psz_icon_url = luaL_strdupornull( L, -1 );
    lua_pop( L, 1 );

    lua_getfield( L, -1, "url" );
    p_desc->psz_url = luaL_strdupornull( L, -1 );
    lua_pop( L, 1 );

    lua_getfield( L, -1, "capabilities" );
    p_desc->i_capabilities = 0;
    if( lua_istable( L, -1 ) )
    {
        /* List all table entries */
        lua_pushnil( L );
        while( lua_next( L, -2 ) != 0 )
        {
            /* Key is at index -2 and value at index -1 */
            const char *psz_cap = luaL_checkstring( L, -1 );
            int i_cap = 0;
            const char *psz_iter;
            for( psz_iter = *ppsz_capabilities; psz_iter;
                 psz_iter = ppsz_capabilities[ ++i_cap ] )
            {
                if( !strcmp( psz_iter, psz_cap ) )
                {
                    p_desc->i_capabilities |= 1 << i_cap;
                    break;
                }
            }

            lua_pop( L, 1 );

            if( !psz_iter )
                msg_Warn( p_sd, "Services discovery capability '%s' unknown in "
                                "script '%s'", psz_cap, p_sys->psz_filename );
        }
    }

    lua_pop( L, 1 );
    i_ret = VLC_SUCCESS;

end:
    lua_close( L );
    return i_ret;

}