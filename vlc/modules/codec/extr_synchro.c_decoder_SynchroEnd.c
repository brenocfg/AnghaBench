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
struct TYPE_3__ {int decoding_start; int* p_tau; int* pi_meaningful; } ;
typedef  TYPE_1__ decoder_synchro_t ;

/* Variables and functions */
 int MAX_PIC_AVERAGE ; 
 int MAX_VALID_TAU ; 
 int vlc_tick_now () ; 

void decoder_SynchroEnd( decoder_synchro_t * p_synchro, int i_coding_type,
                      bool b_garbage )
{
    vlc_tick_t  tau;

    if( b_garbage )
        return;

    tau = vlc_tick_now() - p_synchro->decoding_start;

    /* If duration too high, something happened (pause ?), so don't
     * take it into account. */
    if( tau < 3 * p_synchro->p_tau[i_coding_type] ||
          ( !p_synchro->pi_meaningful[i_coding_type] && tau < MAX_VALID_TAU ) )
    {
        /* Mean with average tau, to ensure stability. */
        p_synchro->p_tau[i_coding_type] =
            (p_synchro->pi_meaningful[i_coding_type]
             * p_synchro->p_tau[i_coding_type] + tau)
            / (p_synchro->pi_meaningful[i_coding_type] + 1);
        if( p_synchro->pi_meaningful[i_coding_type] < MAX_PIC_AVERAGE )
        {
            p_synchro->pi_meaningful[i_coding_type]++;
        }
    }
}