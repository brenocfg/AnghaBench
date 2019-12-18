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
struct TYPE_5__ {int /*<<< orphan*/ * (* pf_packetize ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pf_flush ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ decoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FlushPacketizer( decoder_t *p_packetizer )
{
    if( p_packetizer->pf_flush )
        p_packetizer->pf_flush( p_packetizer );
    else
    {
        block_t *p_block_out;
        while( (p_block_out = p_packetizer->pf_packetize( p_packetizer, NULL )) )
            block_Release( p_block_out );
    }
}