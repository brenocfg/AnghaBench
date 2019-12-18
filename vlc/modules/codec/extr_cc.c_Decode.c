#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ i_reorder_depth; } ;
struct TYPE_14__ {TYPE_1__ cc; } ;
struct TYPE_15__ {TYPE_2__ subs; } ;
struct TYPE_16__ {TYPE_3__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_17__ {scalar_t__ i_reorder_depth; int /*<<< orphan*/  p_cea708; int /*<<< orphan*/  p_dtvcc; scalar_t__ p_eia608; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_18__ {int i_flags; int i_buffer; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int BLOCK_FLAG_TYPE_B ; 
 int /*<<< orphan*/  CEA708_DTVCC_Demuxer_Flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CEA708_Decoder_Flush (int /*<<< orphan*/ ) ; 
 scalar_t__ DoDecode (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Eia608Init (scalar_t__) ; 
 int /*<<< orphan*/  Push (TYPE_4__*,TYPE_6__*) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 

__attribute__((used)) static int Decode( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_block )
    {
        /* Reset decoder if needed */
        if( p_block->i_flags & (BLOCK_FLAG_DISCONTINUITY | BLOCK_FLAG_CORRUPTED) )
        {
            /* Drain */
            for( ; DoDecode( p_dec, true ) ; );
            if( p_sys->p_eia608 )
            {
                Eia608Init( p_sys->p_eia608 );
            }
            else
            {
                CEA708_DTVCC_Demuxer_Flush( p_sys->p_dtvcc );
                CEA708_Decoder_Flush( p_sys->p_cea708 );
            }

            if( (p_block->i_flags & BLOCK_FLAG_CORRUPTED) || p_block->i_buffer < 1 )
            {
                block_Release( p_block );
                return VLCDEC_SUCCESS;
            }
        }

        /* XXX Cc captions data are OUT OF ORDER (because we receive them in the bitstream
         * order (ie ordered by video picture dts) instead of the display order.
         *  We will simulate a simple IPB buffer scheme
         * and reorder with pts.
         * XXX it won't work with H264 which use non out of order B picture or MMCO */
        if( p_sys->i_reorder_depth == 0 )
        {
            /* Wait for a P and output all *previous* picture by pts order (for
             * hierarchical B frames) */
            if( (p_block->i_flags & BLOCK_FLAG_TYPE_B) == 0 )
                for( ; DoDecode( p_dec, true ); );
        }

        Push( p_dec, p_block );
    }

    const bool b_no_reorder = (p_dec->fmt_in.subs.cc.i_reorder_depth < 0);
    for( ; DoDecode( p_dec, (p_block == NULL) || b_no_reorder ); );

    return VLCDEC_SUCCESS;
}