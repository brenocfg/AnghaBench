#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ f_float; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_16__ {scalar_t__ i_buffering_delay; scalar_t__ i_rate_date; scalar_t__ i_rate_delay; scalar_t__ rate_source; scalar_t__ rate; scalar_t__ i_cmd_delay; int /*<<< orphan*/  p_out; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_input; int /*<<< orphan*/  wait; int /*<<< orphan*/  b_paused; } ;
typedef  TYPE_2__ ts_thread_t ;
struct TYPE_17__ {scalar_t__ i_date; int i_type; } ;
typedef  TYPE_3__ ts_cmd_t ;

/* Variables and functions */
#define  C_ADD 131 
#define  C_CONTROL 130 
#define  C_DEL 129 
#define  C_SEND 128 
 int /*<<< orphan*/  CmdCleanAdd (TYPE_3__*) ; 
 int /*<<< orphan*/  CmdCleanControl (TYPE_3__*) ; 
 int /*<<< orphan*/  CmdCleanSend (TYPE_3__*) ; 
 int /*<<< orphan*/  CmdExecuteAdd (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CmdExecuteControl (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CmdExecuteDel (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CmdExecuteSend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  INPUT_CONTROL_SET_RATE ; 
 int /*<<< orphan*/  TsPopCmdLocked (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  cmd_cleanup_routine ; 
 int es_out_GetBuffering (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_SetRate (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  input_ControlPushHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int const) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_tick_wait (scalar_t__) ; 

__attribute__((used)) static void *TsRun( void *p_data )
{
    ts_thread_t *p_ts = p_data;
    vlc_tick_t i_buffering_date = -1;

    for( ;; )
    {
        ts_cmd_t cmd;
        vlc_tick_t  i_deadline;
        bool b_buffering;

        /* Pop a command to execute */
        vlc_mutex_lock( &p_ts->lock );
        mutex_cleanup_push( &p_ts->lock );

        for( ;; )
        {
            const int canc = vlc_savecancel();
            b_buffering = es_out_GetBuffering( p_ts->p_out );

            if( ( !p_ts->b_paused || b_buffering ) && !TsPopCmdLocked( p_ts, &cmd, false ) )
            {
                vlc_restorecancel( canc );
                break;
            }
            vlc_restorecancel( canc );

            vlc_cond_wait( &p_ts->wait, &p_ts->lock );
        }

        if( b_buffering && i_buffering_date < 0 )
        {
            i_buffering_date = cmd.i_date;
        }
        else if( i_buffering_date > 0 )
        {
            p_ts->i_buffering_delay += i_buffering_date - cmd.i_date; /* It is < 0 */
            if( b_buffering )
                i_buffering_date = cmd.i_date;
            else
                i_buffering_date = -1;
        }

        if( p_ts->i_rate_date < 0 )
            p_ts->i_rate_date = cmd.i_date;

        p_ts->i_rate_delay = 0;
        if( p_ts->rate_source != p_ts->rate )
        {
            const vlc_tick_t i_duration = cmd.i_date - p_ts->i_rate_date;
            p_ts->i_rate_delay = i_duration * p_ts->rate_source / p_ts->rate - i_duration;
        }
        if( p_ts->i_cmd_delay + p_ts->i_rate_delay + p_ts->i_buffering_delay < 0 && p_ts->rate != p_ts->rate_source )
        {
            const int canc = vlc_savecancel();

            /* Auto reset to rate 1.0 */
            msg_Warn( p_ts->p_input, "es out timeshift: auto reset rate to %f", p_ts->rate_source );

            p_ts->i_cmd_delay = 0;
            p_ts->i_buffering_delay = 0;

            p_ts->i_rate_delay = 0;
            p_ts->i_rate_date = -1;
            p_ts->rate = p_ts->rate_source;

            if( !es_out_SetRate( p_ts->p_out, p_ts->rate_source, p_ts->rate ) )
            {
                vlc_value_t val = { .f_float = p_ts->rate };
                /* Warn back input
                 * FIXME it is perfectly safe BUT it is ugly as it may hide a
                 * rate change requested by user */
                input_ControlPushHelper( p_ts->p_input, INPUT_CONTROL_SET_RATE, &val );
            }

            vlc_restorecancel( canc );
        }
        i_deadline = cmd.i_date + p_ts->i_cmd_delay + p_ts->i_rate_delay + p_ts->i_buffering_delay;

        vlc_cleanup_pop();
        vlc_mutex_unlock( &p_ts->lock );

        /* Regulate the speed of command processing to the same one than
         * reading  */
        vlc_cleanup_push( cmd_cleanup_routine, &cmd );

        vlc_tick_wait( i_deadline );

        vlc_cleanup_pop();

        /* Execute the command  */
        const int canc = vlc_savecancel();
        switch( cmd.i_type )
        {
        case C_ADD:
            CmdExecuteAdd( p_ts->p_out, &cmd );
            CmdCleanAdd( &cmd );
            break;
        case C_SEND:
            CmdExecuteSend( p_ts->p_out, &cmd );
            CmdCleanSend( &cmd );
            break;
        case C_CONTROL:
            CmdExecuteControl( p_ts->p_out, &cmd );
            CmdCleanControl( &cmd );
            break;
        case C_DEL:
            CmdExecuteDel( p_ts->p_out, &cmd );
            break;
        default:
            vlc_assert_unreachable();
            break;
        }
        vlc_restorecancel( canc );
    }

    return NULL;
}