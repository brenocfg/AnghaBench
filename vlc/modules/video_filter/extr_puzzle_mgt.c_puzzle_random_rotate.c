#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_12__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_10__ {int i_rotate; } ;
struct TYPE_9__ {size_t i_pieces_nbr; } ;
struct TYPE_13__ {TYPE_3__* ps_pieces; TYPE_2__ s_current_param; TYPE_1__ s_allocated; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_11__ {int i_actual_mirror; int /*<<< orphan*/  i_center_y; int /*<<< orphan*/  i_center_x; scalar_t__ i_actual_angle; } ;

/* Variables and functions */
 int /*<<< orphan*/  puzzle_calculate_corners (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  puzzle_rotate_pce (TYPE_4__*,size_t,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_mrand48 () ; 

void puzzle_random_rotate( filter_t *p_filter)
{
    filter_sys_t *p_sys = p_filter->p_sys;
    /* add random rotation to each piece */
    for (uint32_t i = 0; i < p_sys->s_allocated.i_pieces_nbr; i++)
    {
        p_sys->ps_pieces[i].i_actual_angle  = 0;
        p_sys->ps_pieces[i].i_actual_mirror = +1;

        switch ( p_sys->s_current_param.i_rotate )
        {
          case 1:
                puzzle_rotate_pce( p_filter, i, (( (unsigned) vlc_mrand48()) % ( 2 ) ) * 2, p_sys->ps_pieces[i].i_center_x, p_sys->ps_pieces[i].i_center_y, false );
            break;
          case 2:
                puzzle_rotate_pce( p_filter, i, (( (unsigned) vlc_mrand48()) % ( 4 ) ), p_sys->ps_pieces[i].i_center_x, p_sys->ps_pieces[i].i_center_y, false );
            break;
          case 3:
                puzzle_rotate_pce( p_filter, i, (( (unsigned) vlc_mrand48()) % ( 8 ) ), p_sys->ps_pieces[i].i_center_x, p_sys->ps_pieces[i].i_center_y, false );
            break;
        }
        puzzle_calculate_corners( p_filter, i );
    }
}