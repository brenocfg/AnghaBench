#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_13__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_14__ {int /*<<< orphan*/ * p_block; scalar_t__ i_spu; scalar_t__ i_rle_size; scalar_t__ i_spu_size; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ParsePacket (TYPE_1__*) ; 
 TYPE_3__* Reassemble (TYPE_1__*,TYPE_3__*) ; 
 int VLCDEC_SUCCESS ; 
 scalar_t__ block_ChainExtract (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_3__*) ; 
 int /*<<< orphan*/  decoder_QueueSub (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Decode( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t       *p_spu_block;
    subpicture_t  *p_spu;

    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;
    p_spu_block = Reassemble( p_dec, p_block );

    if( ! p_spu_block )
    {
        return VLCDEC_SUCCESS;
    }

    /* FIXME: what the, we shouldn’t need to allocate 64k of buffer --sam. */
    p_sys->i_spu = block_ChainExtract( p_spu_block, p_sys->buffer, 65536 );
    p_sys->i_pts = p_spu_block->i_pts;
    block_ChainRelease( p_spu_block );

    /* Parse and decode */
    p_spu = ParsePacket( p_dec );

    /* reinit context */
    p_sys->i_spu_size = 0;
    p_sys->i_rle_size = 0;
    p_sys->i_spu      = 0;
    p_sys->p_block    = NULL;

    if( p_spu != NULL )
        decoder_QueueSub( p_dec, p_spu );
    return VLCDEC_SUCCESS;
}