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
 int /*<<< orphan*/  str_chars ; 
 int /*<<< orphan*/  str_length ; 
 int /*<<< orphan*/  str_plus ; 
 int /*<<< orphan*/  str_split ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ns_new (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_ns_string ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
strm_string_init(strm_state* state)
{
  strm_ns_string = strm_ns_new(NULL, "string");
  strm_var_def(strm_ns_string, "length", strm_cfunc_value(str_length));
  strm_var_def(strm_ns_string, "split", strm_cfunc_value(str_split));
  strm_var_def(strm_ns_string, "+", strm_cfunc_value(str_plus));
  strm_var_def(strm_ns_string, "chars", strm_cfunc_value(str_chars));
}