#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_5__ {int i_map; int /*<<< orphan*/  p_connection; int /*<<< orphan*/  p_symbols; struct TYPE_5__* p_map; struct TYPE_5__* p_keys; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_key_symbols_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    intf_thread_t *p_intf = (intf_thread_t *)p_this;
    intf_sys_t *p_sys = p_intf->p_sys;

    if( !p_sys )
        return; /* if we were running disabled */

    vlc_cancel( p_sys->thread );
    vlc_join( p_sys->thread, NULL );

    for( int i = 0; i < p_sys->i_map; i++ )
        free( p_sys->p_map[i].p_keys );
    free( p_sys->p_map );
    xcb_key_symbols_free( p_sys->p_symbols );
    xcb_disconnect( p_sys->p_connection );
    free( p_sys );
}