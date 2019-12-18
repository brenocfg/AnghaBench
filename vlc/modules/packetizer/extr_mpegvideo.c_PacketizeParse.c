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
struct TYPE_10__ {int /*<<< orphan*/  i_next_block_flags; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_11__ {scalar_t__* p_buffer; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ PICTURE_STARTCODE ; 
 TYPE_3__* ParseMPEGBlock (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static block_t *PacketizeParse( void *p_private, bool *pb_ts_used, block_t *p_block )
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    /* Check if we have a picture start code */
    *pb_ts_used = p_block->p_buffer[3] == PICTURE_STARTCODE;

    p_block = ParseMPEGBlock( p_dec, p_block );
    if( p_block )
    {
        p_block->i_flags |= p_sys->i_next_block_flags;
        p_sys->i_next_block_flags = 0;
    }
    else *pb_ts_used = false; /* only clear up if output */

    return p_block;
}