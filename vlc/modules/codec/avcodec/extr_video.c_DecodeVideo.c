#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_10__ {int i_last_output_frame; int /*<<< orphan*/  cc; int /*<<< orphan*/  lock; int /*<<< orphan*/  pts; int /*<<< orphan*/  framedrop; scalar_t__ i_late_frames; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_11__ {int i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int DecodeBlock (TYPE_1__*,TYPE_3__**) ; 
 int /*<<< orphan*/  FRAMEDROP_NONE ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  cc_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DecodeVideo( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t **pp_block = p_block ? &p_block : NULL /* drain signal */;

    if( p_block &&
        p_block->i_flags & (BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED) )
    {
        /* Drain */
        if( p_block->i_flags & BLOCK_FLAG_DISCONTINUITY )
            DecodeBlock( p_dec, NULL );
        p_sys->i_late_frames = 0;
        p_sys->i_last_output_frame = -1;
        p_sys->framedrop = FRAMEDROP_NONE;

        vlc_mutex_lock(&p_sys->lock);
        date_Set( &p_sys->pts, VLC_TICK_INVALID ); /* To make sure we recover properly */
        vlc_mutex_unlock(&p_sys->lock);

        cc_Flush( &p_sys->cc );

        if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
        {
            block_Release( p_block );
            p_block = NULL; /* output only */
        }
    }

    return DecodeBlock( p_dec, pp_block );
}