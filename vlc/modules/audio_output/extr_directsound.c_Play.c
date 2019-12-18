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
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int b_playing; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  p_dsbuffer; } ;
typedef  TYPE_1__ aout_stream_sys_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 scalar_t__ DSERR_BUFFERLOST ; 
 scalar_t__ DS_OK ; 
 scalar_t__ FillBuffer (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundBuffer_Play (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Play( vlc_object_t *obj, aout_stream_sys_t *sys,
                     block_t *p_buffer )
{
    HRESULT dsresult;
    dsresult = FillBuffer( obj, sys, p_buffer );
    if( dsresult != DS_OK )
        return dsresult;

    /* start playing the buffer */
    dsresult = IDirectSoundBuffer_Play( sys->p_dsbuffer, 0, 0,
                                        DSBPLAY_LOOPING );
    if( dsresult == DSERR_BUFFERLOST )
    {
        IDirectSoundBuffer_Restore( sys->p_dsbuffer );
        dsresult = IDirectSoundBuffer_Play( sys->p_dsbuffer,
                                            0, 0, DSBPLAY_LOOPING );
    }
    if( dsresult != DS_OK )
        msg_Err( obj, "cannot start playing buffer: (hr=0x%lX)", dsresult );
    else
    {
        vlc_mutex_lock( &sys->lock );
        sys->b_playing = true;
        vlc_cond_signal(&sys->cond);
        vlc_mutex_unlock( &sys->lock );

    }
    return dsresult;
}