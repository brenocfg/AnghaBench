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
 int /*<<< orphan*/  exec_rand ; 
 int /*<<< orphan*/  exec_rnorm ; 
 int /*<<< orphan*/  exec_sample ; 
 int /*<<< orphan*/  rand_seed ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
strm_rand_init(strm_state* state)
{
  strm_var_def(state, "rand_seed", strm_cfunc_value(rand_seed));
  strm_var_def(state, "rand", strm_cfunc_value(exec_rand));
  strm_var_def(state, "rand_norm", strm_cfunc_value(exec_rnorm));
  strm_var_def(state, "sample", strm_cfunc_value(exec_sample));
}