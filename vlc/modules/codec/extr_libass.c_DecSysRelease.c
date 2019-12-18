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
struct TYPE_4__ {scalar_t__ i_refcount; scalar_t__ p_library; scalar_t__ p_renderer; scalar_t__ p_track; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ass_free_track (scalar_t__) ; 
 int /*<<< orphan*/  ass_library_done (scalar_t__) ; 
 int /*<<< orphan*/  ass_renderer_done (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DecSysRelease( decoder_sys_t *p_sys )
{
    /* */
    vlc_mutex_lock( &p_sys->lock );
    p_sys->i_refcount--;
    if( p_sys->i_refcount > 0 )
    {
        vlc_mutex_unlock( &p_sys->lock );
        return;
    }
    vlc_mutex_unlock( &p_sys->lock );
    vlc_mutex_destroy( &p_sys->lock );

    if( p_sys->p_track )
        ass_free_track( p_sys->p_track );
    if( p_sys->p_renderer )
        ass_renderer_done( p_sys->p_renderer );
    if( p_sys->p_library )
        ass_library_done( p_sys->p_library );

    free( p_sys );
}