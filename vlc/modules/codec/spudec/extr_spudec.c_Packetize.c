#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_13__ {int /*<<< orphan*/ * p_block; scalar_t__ i_spu; scalar_t__ i_rle_size; scalar_t__ i_spu_size; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* Reassemble (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 TYPE_3__* block_ChainGather (TYPE_3__*) ; 

__attribute__((used)) static block_t *Packetize( decoder_t *p_dec, block_t **pp_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    if( pp_block == NULL ) /* No Drain */
        return NULL;
    block_t *p_block = *pp_block; *pp_block = NULL;
    if( p_block == NULL )
        return NULL;

    block_t *p_spu = Reassemble( p_dec, p_block );

    if( ! p_spu )
    {
        return NULL;
    }

    p_spu->i_dts = p_spu->i_pts;
    p_spu->i_length = VLC_TICK_INVALID;

    /* reinit context */
    p_sys->i_spu_size = 0;
    p_sys->i_rle_size = 0;
    p_sys->i_spu      = 0;
    p_sys->p_block    = NULL;

    return block_ChainGather( p_spu );
}