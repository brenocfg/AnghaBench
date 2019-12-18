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
struct TYPE_11__ {int /*<<< orphan*/  end_date; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_12__ {scalar_t__ i_pts; scalar_t__ i_length; scalar_t__ i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* Parse (TYPE_1__*,int*,int*,TYPE_3__*,int) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 scalar_t__ date_Increment (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static block_t *Packetize( decoder_t *p_dec, block_t **pp_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t       *p_block;
    int           i_frame_length, i_bits;

    if( !pp_block ) /* No Drain */
        return NULL;
    p_block = *pp_block;
    *pp_block = NULL; /* So the packet doesn't get re-sent */

    p_block = Parse( p_dec, &i_frame_length, &i_bits, p_block, true );
    if( !p_block )
        return NULL;

    p_block->i_pts = p_block->i_dts = date_Get( &p_sys->end_date );
    p_block->i_length = date_Increment( &p_sys->end_date, i_frame_length ) - p_block->i_pts;

    /* Just pass on the incoming frame */
    return p_block;
}