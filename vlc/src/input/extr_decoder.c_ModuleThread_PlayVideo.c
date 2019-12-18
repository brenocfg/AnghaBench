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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct decoder_owner {scalar_t__ i_preroll_end; int b_first; int b_has_data; int paused; scalar_t__ frames_countdown; int /*<<< orphan*/  p_fifo; int /*<<< orphan*/  lock; scalar_t__ b_waiting; int /*<<< orphan*/  wait_acknowledge; int /*<<< orphan*/ * p_vout; int /*<<< orphan*/  dec; } ;
struct TYPE_5__ {scalar_t__ date; int b_force; scalar_t__ b_still; } ;
typedef  TYPE_1__ picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecoderWaitUnblock (struct decoder_owner*) ; 
 scalar_t__ PREROLL_NONE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Flush (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vout_FlushAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_PutPicture (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int ModuleThread_PlayVideo( struct decoder_owner *p_owner, picture_t *p_picture )
{
    decoder_t *p_dec = &p_owner->dec;
    vout_thread_t  *p_vout = p_owner->p_vout;

    if( p_picture->date == VLC_TICK_INVALID )
        /* FIXME: VLC_TICK_INVALID -- verify video_output */
    {
        msg_Warn( p_dec, "non-dated video buffer received" );
        picture_Release( p_picture );
        return VLC_EGENERIC;
    }

    vlc_mutex_lock( &p_owner->lock );
    bool prerolled = p_owner->i_preroll_end != PREROLL_NONE;
    if( prerolled && p_owner->i_preroll_end > p_picture->date )
    {
        vlc_mutex_unlock( &p_owner->lock );
        picture_Release( p_picture );
        return VLC_SUCCESS;
    }

    p_owner->i_preroll_end = PREROLL_NONE;

    if( unlikely(prerolled) )
    {
        msg_Dbg( p_dec, "end of video preroll" );

        if( p_vout )
            vout_FlushAll( p_vout );
    }

    if( p_owner->b_waiting && !p_owner->b_first )
    {
        p_owner->b_has_data = true;
        vlc_cond_signal( &p_owner->wait_acknowledge );
    }

    DecoderWaitUnblock( p_owner );

    if( p_owner->b_waiting )
    {
        assert( p_owner->b_first );
        msg_Dbg( p_dec, "Received first picture" );
        p_owner->b_first = false;
        p_picture->b_force = true;
    }

    vlc_mutex_unlock( &p_owner->lock );

    /* FIXME: The *input* FIFO should not be locked here. This will not work
     * properly if/when pictures are queued asynchronously. */
    vlc_fifo_Lock( p_owner->p_fifo );
    if( unlikely(p_owner->paused) && likely(p_owner->frames_countdown > 0) )
        p_owner->frames_countdown--;
    vlc_fifo_Unlock( p_owner->p_fifo );

    /* */
    if( p_vout == NULL )
    {
        picture_Release( p_picture );
        return VLC_EGENERIC;
    }

    if( p_picture->b_still )
    {
        /* Ensure no earlier higher pts breaks still state */
        vout_Flush( p_vout, p_picture->date );
    }
    vout_PutPicture( p_vout, p_picture );

    return VLC_SUCCESS;
}