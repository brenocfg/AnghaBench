#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int i_nb_inputs; TYPE_1__** pp_inputs; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ sout_mux_t ;
struct TYPE_12__ {unsigned int i_num_pmt; TYPE_3__* pmt; } ;
typedef  TYPE_5__ sout_mux_sys_t ;
struct TYPE_9__ {int i_pid; } ;
struct TYPE_13__ {TYPE_2__ ts; } ;
typedef  TYPE_6__ sout_input_sys_t ;
struct TYPE_10__ {int i_pid; } ;
struct TYPE_8__ {scalar_t__ p_sys; } ;

/* Variables and functions */

__attribute__((used)) static int GetNextFreePID( sout_mux_t *p_mux, int i_pid_start )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;

    restart:
    for(unsigned i=i_pid_start; i<p_sys->i_num_pmt; i++)
    {
        if(p_sys->pmt[i].i_pid == i_pid_start)
        {
            i_pid_start++;
            goto restart;
        }
    }

    for(int i=0; i<p_mux->i_nb_inputs; i++)
    {
        sout_input_sys_t *p_stream = (sout_input_sys_t*)p_mux->pp_inputs[i]->p_sys;
        if(p_stream->ts.i_pid == i_pid_start)
        {
            i_pid_start++;
            goto restart;
        }
    }

    if( i_pid_start > 8190 )
    {
        i_pid_start = 32;
        goto restart;
    }

    return i_pid_start;
}