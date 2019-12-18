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
 int /*<<< orphan*/  ary_avg ; 
 int /*<<< orphan*/  ary_correl ; 
 int /*<<< orphan*/  ary_stdev ; 
 int /*<<< orphan*/  ary_sum ; 
 int /*<<< orphan*/  ary_var ; 
 int /*<<< orphan*/  exec_avg ; 
 int /*<<< orphan*/  exec_correl ; 
 int /*<<< orphan*/  exec_mean_stdev ; 
 int /*<<< orphan*/  exec_mean_variance ; 
 int /*<<< orphan*/  exec_mvavg ; 
 int /*<<< orphan*/  exec_stdev ; 
 int /*<<< orphan*/  exec_sum ; 
 int /*<<< orphan*/  exec_variance ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_array ; 
 int /*<<< orphan*/  strm_rand_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_sort_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_stat_init(strm_state* state)
{
  strm_var_def(state, "sum", strm_cfunc_value(exec_sum));
  strm_var_def(state, "average", strm_cfunc_value(exec_avg));
  strm_var_def(state, "mean", strm_cfunc_value(exec_avg));
  strm_var_def(state, "moving_average", strm_cfunc_value(exec_mvavg));
  strm_var_def(state, "rolling_mean", strm_cfunc_value(exec_mvavg));
  strm_var_def(state, "stdev", strm_cfunc_value(exec_stdev));
  strm_var_def(state, "variance", strm_cfunc_value(exec_variance));
  strm_var_def(state, "mean_stdev", strm_cfunc_value(exec_mean_stdev));
  strm_var_def(state, "mean_variance", strm_cfunc_value(exec_mean_variance));
  strm_var_def(state, "correl", strm_cfunc_value(exec_correl));

  strm_var_def(strm_ns_array, "sum", strm_cfunc_value(ary_sum));
  strm_var_def(strm_ns_array, "average", strm_cfunc_value(ary_avg));
  strm_var_def(strm_ns_array, "stdev", strm_cfunc_value(ary_stdev));
  strm_var_def(strm_ns_array, "variance", strm_cfunc_value(ary_var));
  strm_var_def(strm_ns_array, "correl", strm_cfunc_value(ary_correl));

  strm_rand_init(state);
  strm_sort_init(state);
}