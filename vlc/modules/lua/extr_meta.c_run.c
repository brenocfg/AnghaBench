#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  meta_fetcher_scope_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* pf_validator ) (TYPE_1__ const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ luabatch_context_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  FETCHER_SCOPE_LOCAL ; 
 int /*<<< orphan*/  FETCHER_SCOPE_NETWORK ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* luaL_strdupornull (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlclua_dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int run( vlc_object_t *p_this, const char * psz_filename,
                lua_State * L, const char *luafunction,
                const luabatch_context_t *p_context )
{
    /* Ugly hack to delete previous versions of the fetchart()
     * functions. */
    lua_pushnil( L );
    lua_setglobal( L, luafunction );

    /* Load and run the script(s) */
    if( vlclua_dofile( p_this, L, psz_filename ) )
    {
        msg_Warn( p_this, "Error loading script %s: %s", psz_filename,
                 lua_tostring( L, lua_gettop( L ) ) );
        goto error;
    }


    meta_fetcher_scope_t e_scope = FETCHER_SCOPE_NETWORK; /* default to restricted one */
    lua_getglobal( L, "descriptor" );
    if( lua_isfunction( L, lua_gettop( L ) ) && !lua_pcall( L, 0, 1, 0 ) )
    {
        lua_getfield( L, -1, "scope" );
        char *psz_scope = luaL_strdupornull( L, -1 );
        if ( psz_scope && !strcmp( psz_scope, "local" ) )
            e_scope = FETCHER_SCOPE_LOCAL;
        free( psz_scope );
        lua_pop( L, 1 );
    }
    lua_pop( L, 1 );

    if ( p_context && p_context->pf_validator && !p_context->pf_validator( p_context, e_scope ) )
    {
        msg_Dbg( p_this, "skipping script (unmatched scope) %s", psz_filename );
        goto error;
    }

    lua_getglobal( L, luafunction );

    if( !lua_isfunction( L, lua_gettop( L ) ) )
    {
        msg_Warn( p_this, "Error while running script %s, "
                 "function %s() not found", psz_filename, luafunction );
        goto error;
    }

    if( lua_pcall( L, 0, 1, 0 ) )
    {
        msg_Warn( p_this, "Error while running script %s, "
                 "function %s(): %s", psz_filename, luafunction,
                 lua_tostring( L, lua_gettop( L ) ) );
        goto error;
    }
    return VLC_SUCCESS;

error:
    lua_pop( L, 1 );
    return VLC_EGENERIC;
}