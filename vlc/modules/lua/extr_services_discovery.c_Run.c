#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_7__ {int i_query; char** ppsz_query; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  psz_filename; int /*<<< orphan*/ * L; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  DoSearch (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  LUA_GCCOLLECT ; 
 int /*<<< orphan*/  TAB_ERASE (int,char**,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void* Run( void *data )
{
    services_discovery_t *p_sd = ( services_discovery_t * )data;
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    lua_State *L = p_sys->L;

    int cancel = vlc_savecancel();

    lua_getglobal( L, "main" );
    if( !lua_isfunction( L, lua_gettop( L ) ) || lua_pcall( L, 0, 1, 0 ) )
    {
        msg_Err( p_sd, "Error while running script %s, "
                  "function main(): %s", p_sys->psz_filename,
                  lua_tostring( L, lua_gettop( L ) ) );
        lua_pop( L, 1 );
        vlc_restorecancel( cancel );
        return NULL;
    }
    msg_Dbg( p_sd, "LuaSD script loaded: %s", p_sys->psz_filename );

    /* Force garbage collection, because the core will keep the SD
     * open, but lua will never gc until lua_close(). */
    lua_gc( L, LUA_GCCOLLECT, 0 );

    vlc_restorecancel( cancel );

    /* Main loop to handle search requests */
    vlc_mutex_lock( &p_sys->lock );
    mutex_cleanup_push( &p_sys->lock );
    for( ;; )
    {
        /* Wait for a request */
        if( !p_sys->i_query )
        {
            vlc_cond_wait( &p_sys->cond, &p_sys->lock );
            continue;
        }

        /* Execute one query (protected against cancellation) */
        char *psz_query = p_sys->ppsz_query[p_sys->i_query - 1];
        TAB_ERASE(p_sys->i_query, p_sys->ppsz_query, p_sys->i_query - 1);
        vlc_mutex_unlock( &p_sys->lock );

        cancel = vlc_savecancel();
        DoSearch( p_sd, psz_query );
        free( psz_query );
        /* Force garbage collection, because the core will keep the SD
         * open, but lua will never gc until lua_close(). */
        lua_gc( L, LUA_GCCOLLECT, 0 );
        vlc_restorecancel( cancel );

        vlc_mutex_lock( &p_sys->lock );
    }
    vlc_cleanup_pop();
    vlc_assert_unreachable();
}