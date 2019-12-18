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
 int /*<<< orphan*/  ary_length ; 
 int /*<<< orphan*/  ary_max ; 
 int /*<<< orphan*/  ary_min ; 
 int /*<<< orphan*/  ary_reverse ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ns_array ; 
 int /*<<< orphan*/  strm_ns_new (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
strm_array_init(strm_state* state)
{
  strm_ns_array = strm_ns_new(NULL, "array");
  strm_var_def(strm_ns_array, "length", strm_cfunc_value(ary_length));
  strm_var_def(strm_ns_array, "reverse", strm_cfunc_value(ary_reverse));
  strm_var_def(strm_ns_array, "min", strm_cfunc_value(ary_min));
  strm_var_def(strm_ns_array, "max", strm_cfunc_value(ary_max));
}