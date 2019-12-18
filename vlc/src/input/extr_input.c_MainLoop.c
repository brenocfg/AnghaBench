#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_8__ {scalar_t__ i_int; } ;
struct TYPE_10__ {TYPE_1__ val; } ;
typedef  TYPE_3__ input_control_param_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pf_demux; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_12__ {scalar_t__ i_state; int /*<<< orphan*/  p_es_out; TYPE_2__* master; scalar_t__ b_can_pause; } ;
struct TYPE_9__ {scalar_t__ b_eof; TYPE_4__* p_demux; } ;

/* Variables and functions */
 scalar_t__ Control (int /*<<< orphan*/ *,int,TYPE_3__) ; 
 scalar_t__ ControlIsSeekRequest (int) ; 
 int /*<<< orphan*/  ControlPause (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ControlPop (int /*<<< orphan*/ *,int*,TYPE_3__*,scalar_t__,int) ; 
 scalar_t__ ERROR_S ; 
 int INPUT_CONTROL_SET_STATE ; 
 scalar_t__ INPUT_IDLE_SLEEP ; 
 int /*<<< orphan*/  MainLoopDemux (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MainLoopStatistics (int /*<<< orphan*/ *) ; 
 scalar_t__ MainLoopTryRepeat (int /*<<< orphan*/ *) ; 
 scalar_t__ PAUSE_S ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 scalar_t__ es_out_GetBuffering (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_GetEmpty (int /*<<< orphan*/ ) ; 
 scalar_t__ es_out_GetWakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_Stopped (int /*<<< orphan*/ *) ; 
 TYPE_5__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void MainLoop( input_thread_t *p_input, bool b_interactive )
{
    vlc_tick_t i_intf_update = 0;
    vlc_tick_t i_last_seek_mdate = 0;

    if( b_interactive && var_InheritBool( p_input, "start-paused" ) )
        ControlPause( p_input, vlc_tick_now() );

    bool b_pause_after_eof = b_interactive &&
                           var_InheritBool( p_input, "play-and-pause" );
    bool b_paused_at_eof = false;

    demux_t *p_demux = input_priv(p_input)->master->p_demux;
    const bool b_can_demux = p_demux->pf_demux != NULL;

    while( !input_Stopped( p_input ) && input_priv(p_input)->i_state != ERROR_S )
    {
        vlc_tick_t i_wakeup = -1;
        bool b_paused = input_priv(p_input)->i_state == PAUSE_S;
        /* FIXME if input_priv(p_input)->i_state == PAUSE_S the access/access_demux
         * is paused -> this may cause problem with some of them
         * The same problem can be seen when seeking while paused */
        if( b_paused )
            b_paused = !es_out_GetBuffering( input_priv(p_input)->p_es_out )
                    || input_priv(p_input)->master->b_eof;

        if( !b_paused )
        {
            if( !input_priv(p_input)->master->b_eof )
            {
                bool b_force_update = false;

                MainLoopDemux( p_input, &b_force_update );

                if( b_can_demux )
                    i_wakeup = es_out_GetWakeup( input_priv(p_input)->p_es_out );
                if( b_force_update )
                    i_intf_update = 0;

                b_paused_at_eof = false;
            }
            else if( !es_out_GetEmpty( input_priv(p_input)->p_es_out ) )
            {
                msg_Dbg( p_input, "waiting decoder fifos to empty" );
                i_wakeup = vlc_tick_now() + INPUT_IDLE_SLEEP;
            }
            /* Pause after eof only if the input is pausable.
             * This way we won't trigger timeshifting for nothing */
            else if( b_pause_after_eof && input_priv(p_input)->b_can_pause )
            {
                if( b_paused_at_eof )
                    break;

                input_control_param_t param;
                param.val.i_int = PAUSE_S;

                msg_Dbg( p_input, "pausing at EOF (pause after each)");
                Control( p_input, INPUT_CONTROL_SET_STATE, param );

                b_paused = true;
                b_paused_at_eof = true;
            }
            else
            {
                if( MainLoopTryRepeat( p_input ) )
                    break;
            }

            /* Update interface and statistics */
            vlc_tick_t now = vlc_tick_now();
            if( now >= i_intf_update )
            {
                MainLoopStatistics( p_input );
                i_intf_update = now + VLC_TICK_FROM_MS(250);
            }
        }

        /* Handle control */
        for( ;; )
        {
            vlc_tick_t i_deadline = i_wakeup;

            /* Postpone seeking until ES buffering is complete or at most
             * 125 ms. */
            bool b_postpone = es_out_GetBuffering( input_priv(p_input)->p_es_out )
                            && !input_priv(p_input)->master->b_eof;
            if( b_postpone )
            {
                vlc_tick_t now = vlc_tick_now();

                /* Recheck ES buffer level every 20 ms when seeking */
                if( now < i_last_seek_mdate + VLC_TICK_FROM_MS(125)
                 && (i_deadline < 0 || i_deadline > now + VLC_TICK_FROM_MS(20)) )
                    i_deadline = now + VLC_TICK_FROM_MS(20);
                else
                    b_postpone = false;
            }

            int i_type;
            input_control_param_t param;

            if( ControlPop( p_input, &i_type, &param, i_deadline, b_postpone ) )
            {
                if( b_postpone )
                    continue;
                break; /* Wake-up time reached */
            }

#ifndef NDEBUG
            msg_Dbg( p_input, "control type=%d", i_type );
#endif
            if( Control( p_input, i_type, param ) )
            {
                if( ControlIsSeekRequest( i_type ) )
                    i_last_seek_mdate = vlc_tick_now();
                i_intf_update = 0;
            }

            /* Update the wakeup time */
            if( i_wakeup != 0 )
                i_wakeup = es_out_GetWakeup( input_priv(p_input)->p_es_out );
        }
    }
}