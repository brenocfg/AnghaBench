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
 int /*<<< orphan*/  ary_each ; 
 int /*<<< orphan*/  ary_flatmap ; 
 int /*<<< orphan*/  ary_map ; 
 int /*<<< orphan*/  exec_consec ; 
 int /*<<< orphan*/  exec_count ; 
 int /*<<< orphan*/  exec_cycle ; 
 int /*<<< orphan*/  exec_drop ; 
 int /*<<< orphan*/  exec_each ; 
 int /*<<< orphan*/  exec_filter ; 
 int /*<<< orphan*/  exec_flatmap ; 
 int /*<<< orphan*/  exec_map ; 
 int /*<<< orphan*/  exec_max ; 
 int /*<<< orphan*/  exec_min ; 
 int /*<<< orphan*/  exec_rbk ; 
 int /*<<< orphan*/  exec_reduce ; 
 int /*<<< orphan*/  exec_repeat ; 
 int /*<<< orphan*/  exec_seq ; 
 int /*<<< orphan*/  exec_slice ; 
 int /*<<< orphan*/  exec_take ; 
 int /*<<< orphan*/  exec_uniq ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_array ; 
 int /*<<< orphan*/  strm_stat_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_iter_init(strm_state* state)
{
  strm_var_def(state, "seq", strm_cfunc_value(exec_seq));
  strm_var_def(state, "repeat", strm_cfunc_value(exec_repeat));
  strm_var_def(state, "cycle", strm_cfunc_value(exec_cycle));
  strm_var_def(state, "each", strm_cfunc_value(exec_each));
  strm_var_def(state, "map", strm_cfunc_value(exec_map));
  strm_var_def(state, "flatmap", strm_cfunc_value(exec_flatmap));
  strm_var_def(state, "filter", strm_cfunc_value(exec_filter));
  strm_var_def(state, "count", strm_cfunc_value(exec_count));
  strm_var_def(state, "min", strm_cfunc_value(exec_min));
  strm_var_def(state, "max", strm_cfunc_value(exec_max));
  strm_var_def(state, "reduce", strm_cfunc_value(exec_reduce));
  strm_var_def(state, "reduce_by_key", strm_cfunc_value(exec_rbk));

  strm_var_def(state, "slice", strm_cfunc_value(exec_slice));
  strm_var_def(state, "consec", strm_cfunc_value(exec_consec));
  strm_var_def(state, "take", strm_cfunc_value(exec_take));
  strm_var_def(state, "drop", strm_cfunc_value(exec_drop));
  strm_var_def(state, "uniq", strm_cfunc_value(exec_uniq));

  strm_var_def(strm_ns_array, "each", strm_cfunc_value(ary_each));
  strm_var_def(strm_ns_array, "map", strm_cfunc_value(ary_map));
  strm_var_def(strm_ns_array, "flatmap", strm_cfunc_value(ary_flatmap));
  strm_stat_init(state);
}