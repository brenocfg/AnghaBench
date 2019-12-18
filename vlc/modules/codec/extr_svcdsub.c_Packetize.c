#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* Reassemble (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 

__attribute__((used)) static block_t *Packetize( decoder_t *p_dec, block_t **pp_block )
{
    block_t *p_block, *p_spu;

    if( pp_block == NULL || *pp_block == NULL ) return NULL;

    p_block = *pp_block;
    *pp_block = NULL;

    if( !(p_spu = Reassemble( p_dec, p_block )) ) return NULL;

    p_spu->i_dts = p_spu->i_pts;
    p_spu->i_length = VLC_TICK_INVALID;

    return p_spu;
}