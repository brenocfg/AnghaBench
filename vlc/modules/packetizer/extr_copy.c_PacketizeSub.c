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
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_5__ {int i_flags; scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static block_t *PacketizeSub( decoder_t *p_dec, block_t **pp_block )
{
    block_t *p_block;

    if( pp_block == NULL || *pp_block == NULL )
        return NULL;
    if( (*pp_block)->i_flags&(BLOCK_FLAG_CORRUPTED) )
    {
        block_Release( *pp_block );
        return NULL;
    }

    p_block = *pp_block;
    *pp_block = NULL;

    if( p_block->i_dts == VLC_TICK_INVALID )
    {
        p_block->i_dts = p_block->i_pts;
    }

    if( p_block->i_dts == VLC_TICK_INVALID )
    {
        msg_Dbg( p_dec, "need valid dts" );
        block_Release( p_block );
        return NULL;
    }

    return p_block;
}