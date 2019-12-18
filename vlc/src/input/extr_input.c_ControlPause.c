#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_4__ {scalar_t__ b_can_pause; int /*<<< orphan*/  p_es_out; TYPE_1__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p_demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_SET_PAUSE_STATE ; 
 int PAUSE_S ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ es_out_SetPauseState (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_ChangeState (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ControlPause( input_thread_t *p_input, vlc_tick_t i_control_date )
{
    int i_state = PAUSE_S;

    if( input_priv(p_input)->b_can_pause )
    {
        demux_t *p_demux = input_priv(p_input)->master->p_demux;

        if( demux_Control( p_demux, DEMUX_SET_PAUSE_STATE, true ) )
        {
            msg_Warn( p_input, "cannot set pause state" );
            return;
        }
    }

    /* */
    if( es_out_SetPauseState( input_priv(p_input)->p_es_out, input_priv(p_input)->b_can_pause,
                              true, i_control_date ) )
    {
        msg_Warn( p_input, "cannot set pause state at es_out level" );
        return;
    }

    /* Switch to new state */
    input_ChangeState( p_input, i_state, i_control_date );
}