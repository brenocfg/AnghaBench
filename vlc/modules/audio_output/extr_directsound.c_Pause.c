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
struct TYPE_3__ {int b_playing; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  p_dsbuffer; } ;
typedef  TYPE_1__ aout_stream_sys_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_Play (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundBuffer_Stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Pause( aout_stream_sys_t *sys, bool pause )
{
    HRESULT hr;

    if( pause )
        hr = IDirectSoundBuffer_Stop( sys->p_dsbuffer );
    else
        hr = IDirectSoundBuffer_Play( sys->p_dsbuffer, 0, 0, DSBPLAY_LOOPING );
    if( hr == DS_OK )
    {
        vlc_mutex_lock( &sys->lock );
        sys->b_playing = !pause;
        if( sys->b_playing )
            vlc_cond_signal( &sys->cond );
        vlc_mutex_unlock( &sys->lock );
    }
    return hr;
}