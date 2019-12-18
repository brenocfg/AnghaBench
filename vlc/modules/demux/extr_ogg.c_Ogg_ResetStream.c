#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * p_blocks; int /*<<< orphan*/ ** pp_append; } ;
struct TYPE_7__ {scalar_t__ i_prev_blocksize; } ;
struct TYPE_8__ {TYPE_1__ vorbis; } ;
struct TYPE_10__ {scalar_t__ i_codec; } ;
struct TYPE_11__ {int b_reinit; int b_interpolation_failed; TYPE_3__ queue; int /*<<< orphan*/  os; int /*<<< orphan*/  dts; scalar_t__ i_next_block_flags; int /*<<< orphan*/  i_pcr; TYPE_2__ special; TYPE_4__ fmt; } ;
typedef  TYPE_5__ logical_stream_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_VORBIS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ogg_stream_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Ogg_ResetStream( logical_stream_t *p_stream )
{
#ifdef HAVE_LIBVORBIS
    if ( p_stream->fmt.i_codec == VLC_CODEC_VORBIS )
    {
        p_stream->special.vorbis.i_prev_blocksize = 0;
    }
#endif
    /* we'll trash all the data until we find the next pcr */
    p_stream->b_reinit = true;
    p_stream->i_pcr = VLC_TICK_INVALID;
    p_stream->i_next_block_flags = 0;
    p_stream->b_interpolation_failed = false;
    date_Set( &p_stream->dts, VLC_TICK_INVALID );
    ogg_stream_reset( &p_stream->os );
    block_ChainRelease( p_stream->queue.p_blocks );
    p_stream->queue.p_blocks = NULL;
    p_stream->queue.pp_append = &p_stream->queue.p_blocks;
}