#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b_playing; int /*<<< orphan*/ * p_dsobject; int /*<<< orphan*/ * p_dsbuffer; int /*<<< orphan*/ * p_notify; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  eraser_thread; } ;
typedef  TYPE_1__ aout_stream_sys_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundNotify_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Stop( aout_stream_sys_t *p_sys )
{
    vlc_mutex_lock( &p_sys->lock );
    p_sys->b_playing =  true;
    vlc_cond_signal( &p_sys->cond );
    vlc_mutex_unlock( &p_sys->lock );
    vlc_cancel( p_sys->eraser_thread );
    vlc_join( p_sys->eraser_thread, NULL );
    vlc_cond_destroy( &p_sys->cond );
    vlc_mutex_destroy( &p_sys->lock );

    if( p_sys->p_notify != NULL )
    {
        IDirectSoundNotify_Release(p_sys->p_notify );
        p_sys->p_notify = NULL;
    }
    if( p_sys->p_dsbuffer != NULL )
    {
        IDirectSoundBuffer_Stop( p_sys->p_dsbuffer );
        IDirectSoundBuffer_Release( p_sys->p_dsbuffer );
        p_sys->p_dsbuffer = NULL;
    }
    if( p_sys->p_dsobject != NULL )
    {
        IDirectSound_Release( p_sys->p_dsobject );
        p_sys->p_dsobject = NULL;
    }
    return DS_OK;
}