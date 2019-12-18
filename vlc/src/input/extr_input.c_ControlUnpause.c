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
struct TYPE_4__ {int /*<<< orphan*/  p_es_out; TYPE_1__* master; scalar_t__ b_can_pause; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p_demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_SET_PAUSE_STATE ; 
 int /*<<< orphan*/  ERROR_S ; 
 int /*<<< orphan*/  PLAYING_S ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  es_out_SetPauseState (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_ChangeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ControlUnpause( input_thread_t *p_input, vlc_tick_t i_control_date )
{
    if( input_priv(p_input)->b_can_pause )
    {
        demux_t *p_demux = input_priv(p_input)->master->p_demux;

        if( demux_Control( p_demux, DEMUX_SET_PAUSE_STATE, false ) )
        {
            msg_Err( p_input, "cannot resume" );
            input_ChangeState( p_input, ERROR_S, i_control_date );
            return;
        }
    }

    /* Switch to play */
    input_ChangeState( p_input, PLAYING_S, i_control_date );
    es_out_SetPauseState( input_priv(p_input)->p_es_out, false, false, i_control_date );
}