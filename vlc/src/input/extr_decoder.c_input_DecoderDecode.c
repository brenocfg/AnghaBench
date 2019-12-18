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
struct decoder_owner {int /*<<< orphan*/  p_fifo; int /*<<< orphan*/  wait_fifo; int /*<<< orphan*/  b_waiting; } ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_fifo_DequeueAllUnlocked (int /*<<< orphan*/ ) ; 
 int vlc_fifo_GetBytes (int /*<<< orphan*/ ) ; 
 int vlc_fifo_GetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_QueueUnlocked (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_WaitCond (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void input_DecoderDecode( decoder_t *p_dec, block_t *p_block, bool b_do_pace )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    vlc_fifo_Lock( p_owner->p_fifo );
    if( !b_do_pace )
    {
        /* FIXME: ideally we would check the time amount of data
         * in the FIFO instead of its size. */
        /* 400 MiB, i.e. ~ 50mb/s for 60s */
        if( vlc_fifo_GetBytes( p_owner->p_fifo ) > 400*1024*1024 )
        {
            msg_Warn( p_dec, "decoder/packetizer fifo full (data not "
                      "consumed quickly enough), resetting fifo!" );
            block_ChainRelease( vlc_fifo_DequeueAllUnlocked( p_owner->p_fifo ) );
            p_block->i_flags |= BLOCK_FLAG_DISCONTINUITY;
        }
    }
    else
    if( !p_owner->b_waiting )
    {   /* The FIFO is not consumed when waiting, so pacing would deadlock VLC.
         * Locking is not necessary as b_waiting is only read, not written by
         * the decoder thread. */
        while( vlc_fifo_GetCount( p_owner->p_fifo ) >= 10 )
            vlc_fifo_WaitCond( p_owner->p_fifo, &p_owner->wait_fifo );
    }

    vlc_fifo_QueueUnlocked( p_owner->p_fifo, p_block );
    vlc_fifo_Unlock( p_owner->p_fifo );
}