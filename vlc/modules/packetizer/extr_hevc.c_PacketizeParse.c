#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_ccs; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_12__ {int i_buffer; int* p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* ParseNALBlock (TYPE_1__*,int*,TYPE_3__*) ; 
 int /*<<< orphan*/  cc_storage_commit (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static block_t *PacketizeParse(void *p_private, bool *pb_ts_used, block_t *p_block)
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    /* Remove trailing 0 bytes */
    while (p_block->i_buffer > 5 && p_block->p_buffer[p_block->i_buffer-1] == 0x00 )
        p_block->i_buffer--;

    p_block = ParseNALBlock( p_dec, pb_ts_used, p_block );
    if( p_block )
        cc_storage_commit( p_sys->p_ccs, p_block );

    return p_block;
}