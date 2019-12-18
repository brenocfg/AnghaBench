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
 int /*<<< orphan*/  ary_median ; 
 int /*<<< orphan*/  ary_sort ; 
 int /*<<< orphan*/  ary_sortby ; 
 int /*<<< orphan*/  exec_cmp ; 
 int /*<<< orphan*/  exec_median ; 
 int /*<<< orphan*/  exec_sort ; 
 int /*<<< orphan*/  exec_sortby ; 
 int /*<<< orphan*/  str_ge ; 
 int /*<<< orphan*/  str_gt ; 
 int /*<<< orphan*/  str_le ; 
 int /*<<< orphan*/  str_lt ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_array ; 
 int /*<<< orphan*/ * strm_ns_string ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_sort_init(strm_state* state)
{
  strm_var_def(strm_ns_array, "sort", strm_cfunc_value(ary_sort));
  strm_var_def(strm_ns_array, "sort_by", strm_cfunc_value(ary_sortby));
  strm_var_def(strm_ns_array, "median", strm_cfunc_value(ary_median));
  strm_var_def(state, "cmp", strm_cfunc_value(exec_cmp));
  strm_var_def(state, "sort", strm_cfunc_value(exec_sort));
  strm_var_def(state, "sort_by", strm_cfunc_value(exec_sortby));
  strm_var_def(state, "median", strm_cfunc_value(exec_median));

  strm_var_def(strm_ns_string, "<", strm_cfunc_value(str_lt));
  strm_var_def(strm_ns_string, "<=", strm_cfunc_value(str_le));
  strm_var_def(strm_ns_string, ">", strm_cfunc_value(str_gt));
  strm_var_def(strm_ns_string, ">=", strm_cfunc_value(str_ge));
}