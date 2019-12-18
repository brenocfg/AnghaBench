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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  thread; int /*<<< orphan*/ * hotkeyWindow; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Thread ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    intf_thread_t *p_intf = (intf_thread_t *)p_this;
    intf_sys_t *p_sys = malloc( sizeof (intf_sys_t) );

    if( p_sys == NULL )
        return VLC_ENOMEM;

    p_intf->p_sys = p_sys;
    p_sys->hotkeyWindow = NULL;
    vlc_mutex_init( &p_sys->lock );
    vlc_cond_init( &p_sys->wait );

    if( vlc_clone( &p_sys->thread, Thread, p_intf, VLC_THREAD_PRIORITY_LOW ) )
    {
        vlc_mutex_destroy( &p_sys->lock );
        vlc_cond_destroy( &p_sys->wait );
        free( p_sys );
        p_intf->p_sys = NULL;

        return VLC_ENOMEM;
    }

    vlc_mutex_lock( &p_sys->lock );
    while( p_sys->hotkeyWindow == NULL )
        vlc_cond_wait( &p_sys->wait, &p_sys->lock );
    if( p_sys->hotkeyWindow == INVALID_HANDLE_VALUE )
    {
        vlc_mutex_unlock( &p_sys->lock );
        vlc_join( p_sys->thread, NULL );
        vlc_mutex_destroy( &p_sys->lock );
        vlc_cond_destroy( &p_sys->wait );
        free( p_sys );
        p_intf->p_sys = NULL;

        return VLC_ENOMEM;
    }
    vlc_mutex_unlock( &p_sys->lock );

    return VLC_SUCCESS;
}