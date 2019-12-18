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
struct TYPE_10__ {scalar_t__ i_queue; scalar_t__ i_reorder_depth; TYPE_3__* p_queue; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_11__ {scalar_t__ i_pts; struct TYPE_11__* p_next; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ CC_MAX_REORDER_SIZE ; 
 int /*<<< orphan*/  Pop (TYPE_1__*,int) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

__attribute__((used)) static void Push( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_sys->i_queue >= CC_MAX_REORDER_SIZE )
    {
        block_Release( Pop( p_dec, true ) );
        msg_Warn( p_dec, "Trashing a CC entry" );
    }

    block_t **pp_block;
    /* find insertion point */
    for( pp_block = &p_sys->p_queue; *pp_block ; pp_block = &((*pp_block)->p_next) )
    {
        if( p_block->i_pts == VLC_TICK_INVALID || (*pp_block)->i_pts == VLC_TICK_INVALID )
            continue;
        if( p_block->i_pts < (*pp_block)->i_pts )
        {
            if( p_sys->i_reorder_depth > 0 &&
                p_sys->i_queue < p_sys->i_reorder_depth &&
                pp_block == &p_sys->p_queue )
            {
                msg_Info( p_dec, "Increasing reorder depth to %d", ++p_sys->i_reorder_depth );
            }
            break;
        }
    }
    /* Insert, keeping a pts and/or fifo ordered list */
    p_block->p_next = *pp_block ? *pp_block : NULL;
    *pp_block = p_block;
    p_sys->i_queue++;
}