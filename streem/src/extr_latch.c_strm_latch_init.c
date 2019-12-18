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
 int /*<<< orphan*/  exec_concat ; 
 int /*<<< orphan*/  exec_zip ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_latch_init(strm_state* state)
{
  strm_var_def(state, "&", strm_cfunc_value(exec_zip));
  strm_var_def(state, "zip", strm_cfunc_value(exec_zip));
  strm_var_def(state, "concat", strm_cfunc_value(exec_concat));
}