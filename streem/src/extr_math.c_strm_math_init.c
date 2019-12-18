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
 int /*<<< orphan*/  M_E ; 
 int /*<<< orphan*/  M_PI ; 
 int /*<<< orphan*/  math_ceil ; 
 int /*<<< orphan*/  math_cos ; 
 int /*<<< orphan*/  math_floor ; 
 int /*<<< orphan*/  math_pow ; 
 int /*<<< orphan*/  math_round ; 
 int /*<<< orphan*/  math_sin ; 
 int /*<<< orphan*/  math_sqrt ; 
 int /*<<< orphan*/  math_tan ; 
 int /*<<< orphan*/  math_trunc ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_float_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_math_init(strm_state* state)
{
  strm_var_def(state, "PI", strm_float_value(M_PI));
  strm_var_def(state, "E", strm_float_value(M_E));
  strm_var_def(state, "sqrt", strm_cfunc_value(math_sqrt));
  strm_var_def(state, "sin", strm_cfunc_value(math_sin));
  strm_var_def(state, "cos", strm_cfunc_value(math_cos));
  strm_var_def(state, "tan", strm_cfunc_value(math_tan));
  strm_var_def(state, "pow", strm_cfunc_value(math_pow));
  strm_var_def(state, "round", strm_cfunc_value(math_round));
  strm_var_def(state, "ceil", strm_cfunc_value(math_ceil));
  strm_var_def(state, "floor", strm_cfunc_value(math_floor));
  strm_var_def(state, "trunc", strm_cfunc_value(math_trunc));
  strm_var_def(state, "int", strm_cfunc_value(math_trunc));
}