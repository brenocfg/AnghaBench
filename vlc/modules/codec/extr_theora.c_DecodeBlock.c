#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ packetno; scalar_t__ e_o_s; scalar_t__ b_o_s; int /*<<< orphan*/  granulepos; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_1__ ogg_packet ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_14__ {int b_has_headers; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 scalar_t__ ProcessHeaders (TYPE_2__*) ; 
 void* ProcessPacket (TYPE_2__*,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 

__attribute__((used)) static void *DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    ogg_packet oggpacket;

    /* Block to Ogg packet */
    oggpacket.packet = p_block->p_buffer;
    oggpacket.bytes = p_block->i_buffer;
    oggpacket.granulepos = p_block->i_dts;
    oggpacket.b_o_s = 0;
    oggpacket.e_o_s = 0;
    oggpacket.packetno = 0;

    /* Check for headers */
    if( !p_sys->b_has_headers )
    {
        if( ProcessHeaders( p_dec ) )
        {
            block_Release( p_block );
            return NULL;
        }
        p_sys->b_has_headers = true;
    }

    return ProcessPacket( p_dec, &oggpacket, p_block );
}