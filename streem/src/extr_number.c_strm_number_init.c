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
 int /*<<< orphan*/  num_bar ; 
 int /*<<< orphan*/  num_div ; 
 int /*<<< orphan*/  num_ge ; 
 int /*<<< orphan*/  num_gt ; 
 int /*<<< orphan*/  num_le ; 
 int /*<<< orphan*/  num_lt ; 
 int /*<<< orphan*/  num_minus ; 
 int /*<<< orphan*/  num_mod ; 
 int /*<<< orphan*/  num_mult ; 
 int /*<<< orphan*/  num_number ; 
 int /*<<< orphan*/  num_plus ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_new (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strm_ns_number ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_number_init(strm_state* state)
{
  strm_ns_number = strm_ns_new(NULL, "number");
  strm_var_def(strm_ns_number, "+", strm_cfunc_value(num_plus));
  strm_var_def(strm_ns_number, "-", strm_cfunc_value(num_minus));
  strm_var_def(strm_ns_number, "*", strm_cfunc_value(num_mult));
  strm_var_def(strm_ns_number, "/", strm_cfunc_value(num_div));
  strm_var_def(strm_ns_number, "%", strm_cfunc_value(num_mod));
  strm_var_def(strm_ns_number, "|", strm_cfunc_value(num_bar));
  strm_var_def(strm_ns_number, "<", strm_cfunc_value(num_lt));
  strm_var_def(strm_ns_number, "<=", strm_cfunc_value(num_le));
  strm_var_def(strm_ns_number, ">", strm_cfunc_value(num_gt));
  strm_var_def(strm_ns_number, ">=", strm_cfunc_value(num_ge));
  strm_var_def(state, "number", strm_cfunc_value(num_number));
}