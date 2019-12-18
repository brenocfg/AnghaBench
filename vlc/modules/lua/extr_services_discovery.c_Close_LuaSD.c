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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_6__ {int i_query; int /*<<< orphan*/  L; struct TYPE_6__* psz_filename; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; struct TYPE_6__** ppsz_query; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,TYPE_2__**) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void Close_LuaSD( vlc_object_t *p_this )
{
    services_discovery_t *p_sd = ( services_discovery_t * )p_this;
    services_discovery_sys_t *p_sys = p_sd->p_sys;

    vlc_cancel( p_sys->thread );
    vlc_join( p_sys->thread, NULL );

    for( int i = 0; i < p_sys->i_query; i++ )
        free( p_sys->ppsz_query[i] );
    TAB_CLEAN( p_sys->i_query, p_sys->ppsz_query );

    vlc_cond_destroy( &p_sys->cond );
    vlc_mutex_destroy( &p_sys->lock );
    free( p_sys->psz_filename );
    lua_close( p_sys->L );
    free( p_sys );
}