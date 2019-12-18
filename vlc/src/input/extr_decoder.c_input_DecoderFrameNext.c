#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_2__ {scalar_t__ i_cat; } ;
struct decoder_owner {int /*<<< orphan*/  lock; scalar_t__ p_vout; TYPE_1__ fmt; int /*<<< orphan*/  p_fifo; int /*<<< orphan*/  frames_countdown; int /*<<< orphan*/  paused; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_NextPicture (scalar_t__,scalar_t__*) ; 

void input_DecoderFrameNext( decoder_t *p_dec, vlc_tick_t *pi_duration )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    assert( p_owner->paused );
    *pi_duration = 0;

    vlc_fifo_Lock( p_owner->p_fifo );
    p_owner->frames_countdown++;
    vlc_fifo_Signal( p_owner->p_fifo );
    vlc_fifo_Unlock( p_owner->p_fifo );

    vlc_mutex_lock( &p_owner->lock );
    if( p_owner->fmt.i_cat == VIDEO_ES )
    {
        if( p_owner->p_vout )
            vout_NextPicture( p_owner->p_vout, pi_duration );
    }
    vlc_mutex_unlock( &p_owner->lock );
}