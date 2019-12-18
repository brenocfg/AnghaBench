#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  logger; } ;
struct TYPE_6__ {TYPE_1__ obj; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_7__ {struct TYPE_7__* psz_filename; int /*<<< orphan*/  dtable; int /*<<< orphan*/  L; int /*<<< orphan*/  thread; } ;
typedef  TYPE_3__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_LogDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_fd_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_fd_interrupt (int /*<<< orphan*/ *) ; 

void Close_LuaIntf( vlc_object_t *p_this )
{
    intf_thread_t *p_intf = (intf_thread_t*)p_this;
    intf_sys_t *p_sys = p_intf->p_sys;

    vlclua_fd_interrupt( &p_sys->dtable );
    vlc_join( p_sys->thread, NULL );

    lua_close( p_sys->L );
    vlclua_fd_cleanup( &p_sys->dtable );
    free( p_sys->psz_filename );
    free( p_sys );
    vlc_LogDestroy( p_intf->obj.logger );
}