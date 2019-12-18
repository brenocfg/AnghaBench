#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_5__ {size_t i_pieces_nbr; } ;
struct TYPE_7__ {TYPE_1__ s_allocated; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 size_t NO_PCE ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 size_t* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 scalar_t__ vlc_mrand48 () ; 

int puzzle_generate_rand_pce_list( filter_t *p_filter, int32_t **pi_pce_lst )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    int32_t i_pieces_nbr = p_sys->s_allocated.i_pieces_nbr;

    free( *pi_pce_lst );
    *pi_pce_lst = calloc( i_pieces_nbr, sizeof(**pi_pce_lst) );
    if( !*pi_pce_lst )
        return VLC_ENOMEM;

    for( int32_t i = 0; i < i_pieces_nbr; i++ )
        (*pi_pce_lst)[i] = NO_PCE;

    for( int32_t c = 0; c < i_pieces_nbr; ) {
        int32_t i = ((unsigned)vlc_mrand48()) % i_pieces_nbr;
        if( (*pi_pce_lst)[i] == NO_PCE )
            (*pi_pce_lst)[i] = c++;
    }
    return VLC_SUCCESS;
}