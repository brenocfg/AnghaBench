#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  piece_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_12__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_11__ {int i_pieces_nbr; } ;
struct TYPE_10__ {scalar_t__ i_pieces_nbr; } ;
struct TYPE_13__ {scalar_t__* pi_group_qty; TYPE_6__* ps_pieces_tmp; TYPE_2__ s_allocated; TYPE_6__* ps_pieces; TYPE_1__ s_current_param; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_14__ {scalar_t__ i_group_ID; scalar_t__ b_finished; } ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 TYPE_6__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,int) ; 

int puzzle_sort_layers( filter_t *p_filter)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    int32_t i_idx = 0;
    for (uint32_t i_qty = 1; i_qty <= p_sys->s_current_param.i_pieces_nbr; i_qty++) {
        /* pieces at the wrong place are in foreground */
        for (uint32_t i_pce_loop = 0; i_pce_loop < p_sys->s_current_param.i_pieces_nbr; i_pce_loop++) {
            uint32_t i_grp = p_sys->ps_pieces[i_pce_loop].i_group_ID;
            if ( p_sys->pi_group_qty[i_grp] == (int32_t)i_qty ) {
                bool b_check_ok = true;
                for (int32_t i_pce_check = 0; i_pce_check < i_idx; i_pce_check++)
                    if ( p_sys->ps_pieces_tmp[i_pce_check].i_group_ID == i_grp )
                        b_check_ok = false;
                if ( b_check_ok )
                    for (uint32_t i_pce = i_pce_loop; i_pce < p_sys->s_current_param.i_pieces_nbr; i_pce++)
                        if (( p_sys->ps_pieces[i_pce].i_group_ID == i_grp ) && !p_sys->ps_pieces[i_pce].b_finished ) {
                            memcpy( &p_sys->ps_pieces_tmp[i_idx], &p_sys->ps_pieces[i_pce], sizeof(piece_t));
                            i_idx++;
                        }
            }
        }
        /* pieces at the final location are in background */
        for (uint32_t i_pce_loop = 0; i_pce_loop < p_sys->s_current_param.i_pieces_nbr; i_pce_loop++) {
            uint32_t i_grp = p_sys->ps_pieces[i_pce_loop].i_group_ID;
            if ( p_sys->pi_group_qty[i_grp] == (int32_t)i_qty ) {
                bool b_check_ok = true;
                for (int32_t i_pce_check = 0; i_pce_check < i_idx; i_pce_check++)
                    if ( p_sys->ps_pieces_tmp[i_pce_check].i_group_ID == i_grp && p_sys->ps_pieces_tmp[i_pce_check].b_finished )
                        b_check_ok = false;
                if ( b_check_ok )
                    for (uint32_t i_pce = i_pce_loop; i_pce < p_sys->s_current_param.i_pieces_nbr; i_pce++)
                        if (( p_sys->ps_pieces[i_pce].i_group_ID == i_grp ) && p_sys->ps_pieces[i_pce].b_finished ) {
                            memcpy( &p_sys->ps_pieces_tmp[i_idx], &p_sys->ps_pieces[i_pce], sizeof(piece_t));
                            i_idx++;
                        }
            }
        }
    }

    free( p_sys->ps_pieces );
    p_sys->ps_pieces = p_sys->ps_pieces_tmp;
    p_sys->ps_pieces_tmp = malloc( sizeof( piece_t) * p_sys->s_allocated.i_pieces_nbr );
    if (!p_sys->ps_pieces_tmp)
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}