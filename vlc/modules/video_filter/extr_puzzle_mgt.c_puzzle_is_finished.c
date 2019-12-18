#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {size_t i_pieces_nbr; } ;
struct TYPE_5__ {TYPE_1__ s_allocated; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */

bool puzzle_is_finished( filter_sys_t *p_sys, int32_t *pi_pce_lst )
{
    for( uint32_t i = 0; i < p_sys->s_allocated.i_pieces_nbr; i++ )
        if( (int32_t)i != pi_pce_lst[i] )
            return false;

    return true;
}