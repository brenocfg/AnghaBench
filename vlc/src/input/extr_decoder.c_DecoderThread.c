#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {scalar_t__ i_cat; } ;
struct TYPE_4__ {TYPE_1__ fmt_out; } ;
struct decoder_owner {int flushing; int reset_out_state; int paused; scalar_t__ pause_date; float request_rate; scalar_t__ delay; scalar_t__ frames_countdown; int b_idle; int b_draining; int drained; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_acknowledge; int /*<<< orphan*/  p_fifo; int /*<<< orphan*/ * p_aout; TYPE_2__ dec; int /*<<< orphan*/  wait_fifo; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  DecoderThread_ChangeDelay (struct decoder_owner*,scalar_t__) ; 
 int /*<<< orphan*/  DecoderThread_ChangePause (struct decoder_owner*,int,scalar_t__) ; 
 int /*<<< orphan*/  DecoderThread_ChangeRate (struct decoder_owner*,float) ; 
 int /*<<< orphan*/  DecoderThread_Flush (struct decoder_owner*) ; 
 int /*<<< orphan*/  DecoderThread_ProcessInput (struct decoder_owner*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_DecDrain (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_CleanupPush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_fifo_DequeueUnlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

__attribute__((used)) static void *DecoderThread( void *p_data )
{
    struct decoder_owner *p_owner = (struct decoder_owner *)p_data;
    float rate = 1.f;
    vlc_tick_t delay = 0;
    bool paused = false;

    /* The decoder's main loop */
    vlc_fifo_Lock( p_owner->p_fifo );
    vlc_fifo_CleanupPush( p_owner->p_fifo );

    for( ;; )
    {
        if( p_owner->flushing )
        {   /* Flush before/regardless of pause. We do not want to resume just
             * for the sake of flushing (glitches could otherwise happen). */
            int canc = vlc_savecancel();

            vlc_fifo_Unlock( p_owner->p_fifo );

            /* Flush the decoder (and the output) */
            DecoderThread_Flush( p_owner );

            vlc_fifo_Lock( p_owner->p_fifo );
            vlc_restorecancel( canc );

            /* Reset flushing after DecoderThread_ProcessInput in case input_DecoderFlush
             * is called again. This will avoid a second useless flush (but
             * harmless). */
            p_owner->flushing = false;

            continue;
        }

        /* Reset the original pause/rate state when a new aout/vout is created:
         * this will trigger the DecoderThread_ChangePause/DecoderThread_ChangeRate code path
         * if needed. */
        if( p_owner->reset_out_state )
        {
            rate = 1.f;
            paused = false;
            delay = 0;
            p_owner->reset_out_state = false;
        }

        if( paused != p_owner->paused )
        {   /* Update playing/paused status of the output */
            int canc = vlc_savecancel();
            vlc_tick_t date = p_owner->pause_date;

            paused = p_owner->paused;
            vlc_fifo_Unlock( p_owner->p_fifo );

            DecoderThread_ChangePause( p_owner, paused, date );

            vlc_restorecancel( canc );
            vlc_fifo_Lock( p_owner->p_fifo );
            continue;
        }

        if( rate != p_owner->request_rate )
        {
            int canc = vlc_savecancel();

            rate = p_owner->request_rate;
            vlc_fifo_Unlock( p_owner->p_fifo );

            DecoderThread_ChangeRate( p_owner, rate );

            vlc_restorecancel( canc );
            vlc_fifo_Lock( p_owner->p_fifo );
        }

        if( delay != p_owner->delay )
        {
            int canc = vlc_savecancel();

            delay = p_owner->delay;
            vlc_fifo_Unlock( p_owner->p_fifo );

            DecoderThread_ChangeDelay( p_owner, delay );

            vlc_restorecancel( canc );
            vlc_fifo_Lock( p_owner->p_fifo );
        }

        if( p_owner->paused && p_owner->frames_countdown == 0 )
        {   /* Wait for resumption from pause */
            p_owner->b_idle = true;
            vlc_cond_signal( &p_owner->wait_acknowledge );
            vlc_fifo_Wait( p_owner->p_fifo );
            p_owner->b_idle = false;
            continue;
        }

        vlc_cond_signal( &p_owner->wait_fifo );
        vlc_testcancel(); /* forced expedited cancellation in case of stop */

        block_t *p_block = vlc_fifo_DequeueUnlocked( p_owner->p_fifo );
        if( p_block == NULL )
        {
            if( likely(!p_owner->b_draining) )
            {   /* Wait for a block to decode (or a request to drain) */
                p_owner->b_idle = true;
                vlc_cond_signal( &p_owner->wait_acknowledge );
                vlc_fifo_Wait( p_owner->p_fifo );
                p_owner->b_idle = false;
                continue;
            }
            /* We have emptied the FIFO and there is a pending request to
             * drain. Pass p_block = NULL to decoder just once. */
        }

        vlc_fifo_Unlock( p_owner->p_fifo );

        int canc = vlc_savecancel();
        DecoderThread_ProcessInput( p_owner, p_block );

        if( p_block == NULL && p_owner->dec.fmt_out.i_cat == AUDIO_ES )
        {   /* Draining: the decoder is drained and all decoded buffers are
             * queued to the output at this point. Now drain the output. */
            if( p_owner->p_aout != NULL )
                aout_DecDrain( p_owner->p_aout );
        }
        vlc_restorecancel( canc );

        /* TODO? Wait for draining instead of polling. */
        vlc_mutex_lock( &p_owner->lock );
        vlc_fifo_Lock( p_owner->p_fifo );
        if( p_owner->b_draining && (p_block == NULL) )
        {
            p_owner->b_draining = false;
            p_owner->drained = true;
        }
        vlc_cond_signal( &p_owner->wait_acknowledge );
        vlc_mutex_unlock( &p_owner->lock );
    }
    vlc_cleanup_pop();
    vlc_assert_unreachable();
}