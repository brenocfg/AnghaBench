#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  strm_state ;

/* Variables and functions */
 int /*<<< orphan*/ * ns_time ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_new (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_day ; 
 int /*<<< orphan*/  time_hour ; 
 int /*<<< orphan*/  time_min ; 
 int /*<<< orphan*/  time_minus ; 
 int /*<<< orphan*/  time_month ; 
 int /*<<< orphan*/  time_nanosec ; 
 int /*<<< orphan*/  time_now ; 
 int /*<<< orphan*/  time_num ; 
 int /*<<< orphan*/  time_plus ; 
 int /*<<< orphan*/  time_sec ; 
 int /*<<< orphan*/  time_str ; 
 int /*<<< orphan*/  time_time ; 
 int /*<<< orphan*/  time_weekday ; 
 int /*<<< orphan*/  time_year ; 

void
strm_time_init(strm_state* state)
{
  strm_var_def(state, "now", strm_cfunc_value(time_now));
  strm_var_def(state, "time", strm_cfunc_value(time_time));

  ns_time = strm_ns_new(NULL, "time");
  strm_var_def(ns_time, "+", strm_cfunc_value(time_plus));
  strm_var_def(ns_time, "-", strm_cfunc_value(time_minus));
  strm_var_def(ns_time, "string", strm_cfunc_value(time_str));
  strm_var_def(ns_time, "number", strm_cfunc_value(time_num));
  strm_var_def(ns_time, "year", strm_cfunc_value(time_year));
  strm_var_def(ns_time, "month", strm_cfunc_value(time_month));
  strm_var_def(ns_time, "day", strm_cfunc_value(time_day));
  strm_var_def(ns_time, "hour", strm_cfunc_value(time_hour));
  strm_var_def(ns_time, "minute", strm_cfunc_value(time_min));
  strm_var_def(ns_time, "second", strm_cfunc_value(time_sec));
  strm_var_def(ns_time, "nanosecond", strm_cfunc_value(time_nanosec));
  strm_var_def(ns_time, "weekday", strm_cfunc_value(time_weekday));
}