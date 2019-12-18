#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_10__ {scalar_t__ b_blackslot; } ;
struct TYPE_9__ {size_t i_pieces_nbr; } ;
struct TYPE_12__ {size_t* pi_order; size_t i_selected; int b_shuffle_rqst; int b_finished; TYPE_2__ s_current_param; TYPE_1__ s_allocated; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 size_t NO_PCE ; 
 int VLC_SUCCESS ; 
 int puzzle_generate_rand_pce_list (TYPE_3__*,size_t**) ; 
 scalar_t__ puzzle_is_finished (TYPE_4__*,size_t*) ; 
 int /*<<< orphan*/  puzzle_is_valid (TYPE_4__*,size_t*) ; 

int puzzle_shuffle( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    int32_t i_pieces_nbr = p_sys->s_allocated.i_pieces_nbr;

    do
    {
        int i_ret = puzzle_generate_rand_pce_list( p_filter, &p_sys->pi_order );
        if (i_ret != VLC_SUCCESS)
            return i_ret;
    } while( puzzle_is_finished( p_sys, p_sys->pi_order ) || !puzzle_is_valid( p_sys, p_sys->pi_order ) );


    if( p_sys->s_current_param.b_blackslot ) {
        for( int32_t i = 0; i < i_pieces_nbr; i++ )
            if( p_sys->pi_order[i] == i_pieces_nbr - 1 ) {
                p_sys->i_selected = i;
                break;
            }
    }
    else {
        p_sys->i_selected = NO_PCE;
    }

    p_sys->b_shuffle_rqst = false;
    p_sys->b_finished = false;

    return VLC_SUCCESS;
}