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
 int /*<<< orphan*/  csv ; 
 int /*<<< orphan*/  ltsv ; 
 int /*<<< orphan*/  str_number ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_string ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsv ; 

void
strm_csv_init(strm_state* state)
{
  strm_var_def(state, "csv", strm_cfunc_value(csv));
  strm_var_def(state, "tsv", strm_cfunc_value(tsv));
  strm_var_def(state, "ltsv", strm_cfunc_value(ltsv));

  strm_var_def(strm_ns_string, "number", strm_cfunc_value(str_number));
}