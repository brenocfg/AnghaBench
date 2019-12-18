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
typedef  int /*<<< orphan*/  vlc_mutex_t ;
struct TYPE_4__ {int ref_count; int /*<<< orphan*/  p_libvlc_int; int /*<<< orphan*/  instance_lock; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_InternalCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_InternalDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_Quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_threads_deinit () ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_release( libvlc_instance_t *p_instance )
{
    vlc_mutex_t *lock = &p_instance->instance_lock;
    int refs;

    vlc_mutex_lock( lock );
    assert( p_instance->ref_count > 0 );
    refs = --p_instance->ref_count;
    vlc_mutex_unlock( lock );

    if( refs == 0 )
    {
        vlc_mutex_destroy( lock );
        libvlc_Quit( p_instance->p_libvlc_int );
        libvlc_InternalCleanup( p_instance->p_libvlc_int );
        libvlc_InternalDestroy( p_instance->p_libvlc_int );
        free( p_instance );
        libvlc_threads_deinit ();
    }
}