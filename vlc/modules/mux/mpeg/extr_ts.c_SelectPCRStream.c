#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_nb_inputs; TYPE_5__** pp_inputs; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ sout_mux_t ;
struct TYPE_13__ {TYPE_5__* p_pcr_input; } ;
typedef  TYPE_4__ sout_mux_sys_t ;
struct TYPE_14__ {scalar_t__ p_sys; TYPE_1__* p_fmt; } ;
typedef  TYPE_5__ sout_input_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_pid; } ;
struct TYPE_15__ {TYPE_2__ ts; } ;
typedef  TYPE_6__ sout_input_sys_t ;
struct TYPE_10__ {scalar_t__ i_cat; } ;

/* Variables and functions */
 scalar_t__ SPU_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SelectPCRStream( sout_mux_t *p_mux, sout_input_t *p_removed_pcr_input )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;

    /* Find a new pcr stream (Prefer Video Stream) */
    if( p_removed_pcr_input != NULL )
        p_sys->p_pcr_input = NULL;

    for ( int i = 0; i < p_mux->i_nb_inputs; i++ )
    {
        sout_input_t *p_input = p_mux->pp_inputs[i];
        if( p_input == p_removed_pcr_input )
            continue;

        if( p_input->p_fmt->i_cat == VIDEO_ES &&
           (p_sys->p_pcr_input == NULL ||
            p_sys->p_pcr_input->p_fmt->i_cat != VIDEO_ES) )
        {
            p_sys->p_pcr_input = p_input;
            break;
        }
        else if( p_input->p_fmt->i_cat != SPU_ES &&
                 p_sys->p_pcr_input == NULL )
        {
            p_sys->p_pcr_input = p_input;
        }
    }

    if( p_sys->p_pcr_input )
    {
        /* Empty TS buffer */
        /* FIXME */
        msg_Dbg( p_mux, "new PCR PID is %d",
                 ((sout_input_sys_t *)p_sys->p_pcr_input->p_sys)->ts.i_pid );
    }

}