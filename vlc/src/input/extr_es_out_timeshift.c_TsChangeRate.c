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
struct TYPE_3__ {int i_rate_date; float rate; float rate_source; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_out; scalar_t__ i_rate_delay; int /*<<< orphan*/  i_cmd_delay; } ;
typedef  TYPE_1__ ts_thread_t ;

/* Variables and functions */
 int es_out_SetRate (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int TsChangeRate( ts_thread_t *p_ts, float src_rate, float rate )
{
    int i_ret;

    vlc_mutex_lock( &p_ts->lock );
    p_ts->i_cmd_delay += p_ts->i_rate_delay;

    p_ts->i_rate_date = -1;
    p_ts->i_rate_delay = 0;
    p_ts->rate = rate;
    p_ts->rate_source = src_rate;

    i_ret = es_out_SetRate( p_ts->p_out, rate, rate );
    vlc_mutex_unlock( &p_ts->lock );

    return i_ret;
}