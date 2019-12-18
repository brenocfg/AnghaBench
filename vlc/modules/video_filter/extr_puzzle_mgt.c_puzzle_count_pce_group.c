#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_7__ {int i_pieces_nbr; } ;
struct TYPE_9__ {TYPE_1__* ps_pieces; int /*<<< orphan*/ * pi_group_qty; TYPE_2__ s_allocated; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_6__ {size_t i_group_ID; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void puzzle_count_pce_group( filter_t *p_filter) { /* count pce in each group */
    filter_sys_t *p_sys = p_filter->p_sys;

    memset ( p_sys->pi_group_qty, 0, sizeof( int32_t ) * (p_sys->s_allocated.i_pieces_nbr) );
    for (uint32_t i_pce = 0; i_pce < p_sys->s_allocated.i_pieces_nbr; i_pce++)
        p_sys->pi_group_qty[p_sys->ps_pieces[i_pce].i_group_ID]++;
}