#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  piece_t ;
typedef  int /*<<< orphan*/  piece_in_plane_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_7__ {int i_pieces_nbr; int i_rows; int i_cols; int i_planes; } ;
struct TYPE_9__ {TYPE_6__* ps_pieces_tmp; TYPE_6__* ps_pieces; TYPE_1__ s_allocated; void* pi_group_qty; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_10__ {struct TYPE_10__* ps_piece_in_plane; } ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  puzzle_free_ps_pieces (TYPE_2__*) ; 

int puzzle_allocate_ps_pieces( filter_t *p_filter)
{
    filter_sys_t *p_sys = p_filter->p_sys;
    puzzle_free_ps_pieces(p_filter);
    p_sys->s_allocated.i_pieces_nbr = p_sys->s_allocated.i_rows * p_sys->s_allocated.i_cols;
    p_sys->ps_pieces = malloc( sizeof( piece_t) * p_sys->s_allocated.i_pieces_nbr );
    if( !p_sys->ps_pieces )
        return VLC_ENOMEM;
    for (uint32_t p = 0; p < p_sys->s_allocated.i_pieces_nbr; p++) {
        p_sys->ps_pieces[p].ps_piece_in_plane = malloc( sizeof( piece_in_plane_t) * p_sys->s_allocated.i_planes );
        if( !p_sys->ps_pieces[p].ps_piece_in_plane ) {
            for (uint32_t i=0;i<p;i++)
                free(p_sys->ps_pieces[i].ps_piece_in_plane);
            free(p_sys->ps_pieces);
            p_sys->ps_pieces = NULL;
            return VLC_ENOMEM;
        }
    }

    p_sys->ps_pieces_tmp = malloc( sizeof( piece_t) * p_sys->s_allocated.i_pieces_nbr );
    if( !p_sys->ps_pieces_tmp ) {
        for (uint32_t i=0;i<p_sys->s_allocated.i_pieces_nbr;i++)
            free(p_sys->ps_pieces[i].ps_piece_in_plane);
        free(p_sys->ps_pieces);
        p_sys->ps_pieces = NULL;
        return VLC_ENOMEM;
    }
    p_sys->pi_group_qty = malloc( sizeof( int32_t ) * (p_sys->s_allocated.i_pieces_nbr));
    if( !p_sys->pi_group_qty ) {
        for (uint32_t i=0;i<p_sys->s_allocated.i_pieces_nbr;i++)
            free(p_sys->ps_pieces[i].ps_piece_in_plane);
        free(p_sys->ps_pieces);
        p_sys->ps_pieces = NULL;
        free(p_sys->ps_pieces_tmp);
        p_sys->ps_pieces_tmp = NULL;
        return VLC_ENOMEM;
    }
    return VLC_SUCCESS;
}