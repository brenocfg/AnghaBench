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
typedef  int vlc_tick_t ;
struct TYPE_3__ {int i_dts; int i_length; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */

__attribute__((used)) static void OggSetDate( block_t *p_og, vlc_tick_t i_dts, vlc_tick_t i_length )
{
    int i_count;
    block_t *p_tmp;
    vlc_tick_t i_delta;

    for( p_tmp = p_og, i_count = 0; p_tmp != NULL; p_tmp = p_tmp->p_next )
    {
        i_count++;
    }

    if( i_count == 0 ) return; /* ignore. */

    i_delta = i_length / i_count;

    for( p_tmp = p_og; p_tmp != NULL; p_tmp = p_tmp->p_next )
    {
        p_tmp->i_dts    = i_dts;
        p_tmp->i_length = i_delta;

        i_dts += i_delta;
    }
}