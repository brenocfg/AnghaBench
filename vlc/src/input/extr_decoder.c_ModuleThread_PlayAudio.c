#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct decoder_owner {scalar_t__ i_preroll_end; int b_has_data; int /*<<< orphan*/  reload; int /*<<< orphan*/ * p_aout; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_acknowledge; scalar_t__ b_waiting; int /*<<< orphan*/  dec; } ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_5__ {scalar_t__ i_pts; } ;
typedef  TYPE_1__ block_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int AOUT_DEC_CHANGED ; 
 int AOUT_DEC_FAILED ; 
 int /*<<< orphan*/  DecoderWaitUnblock (struct decoder_owner*) ; 
 scalar_t__ PREROLL_NONE ; 
 int /*<<< orphan*/  RELOAD_DECODER_AOUT ; 
 int /*<<< orphan*/  RequestReload (struct decoder_owner*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  aout_DecFlush (int /*<<< orphan*/ *) ; 
 int aout_DecPlay (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ModuleThread_PlayAudio( struct decoder_owner *p_owner, block_t *p_audio )
{
    decoder_t *p_dec = &p_owner->dec;

    assert( p_audio != NULL );

    if( p_audio->i_pts == VLC_TICK_INVALID ) // FIXME --VLC_TICK_INVALID verify audio_output/*
    {
        msg_Warn( p_dec, "non-dated audio buffer received" );
        block_Release( p_audio );
        return VLC_EGENERIC;
    }

    vlc_mutex_lock( &p_owner->lock );
    bool prerolled = p_owner->i_preroll_end != PREROLL_NONE;
    if( prerolled && p_owner->i_preroll_end > p_audio->i_pts )
    {
        vlc_mutex_unlock( &p_owner->lock );
        block_Release( p_audio );
        return VLC_SUCCESS;
    }

    p_owner->i_preroll_end = PREROLL_NONE;
    vlc_mutex_unlock( &p_owner->lock );

    if( unlikely(prerolled) )
    {
        msg_Dbg( p_dec, "end of audio preroll" );

        if( p_owner->p_aout )
            aout_DecFlush( p_owner->p_aout );
    }

    /* */
    /* */
    vlc_mutex_lock( &p_owner->lock );
    if( p_owner->b_waiting )
    {
        p_owner->b_has_data = true;
        vlc_cond_signal( &p_owner->wait_acknowledge );
    }

    /* */
    DecoderWaitUnblock( p_owner );
    vlc_mutex_unlock( &p_owner->lock );

    audio_output_t *p_aout = p_owner->p_aout;

    if( p_aout == NULL )
    {
        msg_Dbg( p_dec, "discarded audio buffer" );
        block_Release( p_audio );
        return VLC_EGENERIC;
    }

    int status = aout_DecPlay( p_aout, p_audio );
    if( status == AOUT_DEC_CHANGED )
    {
        /* Only reload the decoder */
        RequestReload( p_owner );
    }
    else if( status == AOUT_DEC_FAILED )
    {
        /* If we reload because the aout failed, we should release it. That
            * way, a next call to ModuleThread_UpdateAudioFormat() won't re-use the
            * previous (failing) aout but will try to create a new one. */
        atomic_store( &p_owner->reload, RELOAD_DECODER_AOUT );
    }
    return VLC_SUCCESS;
}