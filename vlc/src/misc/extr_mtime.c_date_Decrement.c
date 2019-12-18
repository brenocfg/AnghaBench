#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ date; scalar_t__ i_divider_den; scalar_t__ i_divider_num; unsigned int i_remainder; } ;
typedef  TYPE_1__ date_t ;

/* Variables and functions */
 scalar_t__ CLOCK_FREQ ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int) ; 

vlc_tick_t date_Decrement( date_t *p_date, uint32_t i_nb_samples )
{
    if(unlikely(p_date->date == VLC_TICK_INVALID))
        return VLC_TICK_INVALID;
    vlc_tick_t i_dividend = (vlc_tick_t)i_nb_samples * CLOCK_FREQ * p_date->i_divider_den;
    p_date->date -= i_dividend / p_date->i_divider_num;
    unsigned i_rem_adjust = i_dividend % p_date->i_divider_num;

    if( p_date->i_remainder < i_rem_adjust )
    {
        /* This is Bresenham algorithm. */
        assert( p_date->i_remainder < p_date->i_divider_num);
        p_date->date -= 1;
        p_date->i_remainder += p_date->i_divider_num;
    }

    p_date->i_remainder -= i_rem_adjust;

    return p_date->date;
}