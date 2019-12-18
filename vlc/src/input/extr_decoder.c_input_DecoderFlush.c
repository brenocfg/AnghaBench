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
struct TYPE_2__ {scalar_t__ i_cat; } ;
struct decoder_owner {int flushing; scalar_t__ frames_countdown; int /*<<< orphan*/  p_fifo; TYPE_1__ fmt; scalar_t__ paused; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 scalar_t__ SPU_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_DequeueAllUnlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 

void input_DecoderFlush( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    vlc_fifo_Lock( p_owner->p_fifo );

    /* Empty the fifo */
    block_ChainRelease( vlc_fifo_DequeueAllUnlocked( p_owner->p_fifo ) );

    /* Don't need to wait for the DecoderThread to flush. Indeed, if called a
     * second time, this function will clear the FIFO again before anything was
     * dequeued by DecoderThread and there is no need to flush a second time in
     * a row. */
    p_owner->flushing = true;

    /* Flush video/spu decoder when paused: increment frames_countdown in order
     * to display one frame/subtitle */
    if( p_owner->paused
     && ( p_owner->fmt.i_cat == VIDEO_ES || p_owner->fmt.i_cat == SPU_ES )
     && p_owner->frames_countdown == 0 )
        p_owner->frames_countdown++;

    vlc_fifo_Signal( p_owner->p_fifo );

    vlc_fifo_Unlock( p_owner->p_fifo );
}