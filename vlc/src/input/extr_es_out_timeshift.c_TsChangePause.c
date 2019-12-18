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
struct TYPE_3__ {scalar_t__ i_pause_date; int b_paused; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  i_cmd_delay; int /*<<< orphan*/  p_out; } ;
typedef  TYPE_1__ ts_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int es_out_SetPauseState (int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int TsChangePause( ts_thread_t *p_ts, bool b_source_paused, bool b_paused, vlc_tick_t i_date )
{
    vlc_mutex_lock( &p_ts->lock );

    int i_ret;
    if( b_paused )
    {
        assert( !b_source_paused );
        i_ret = es_out_SetPauseState( p_ts->p_out, true, true, i_date );
    }
    else
    {
        i_ret = es_out_SetPauseState( p_ts->p_out, false, false, i_date );
    }

    if( !i_ret )
    {
        if( !b_paused )
        {
            assert( p_ts->i_pause_date > 0 );

            p_ts->i_cmd_delay += i_date - p_ts->i_pause_date;
        }

        p_ts->b_paused = b_paused;
        p_ts->i_pause_date = i_date;

        vlc_cond_signal( &p_ts->wait );
    }
    vlc_mutex_unlock( &p_ts->lock );
    return i_ret;
}