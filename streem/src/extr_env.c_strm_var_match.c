#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
struct TYPE_4__ {scalar_t__ env; } ;
typedef  TYPE_1__ strm_state ;
typedef  int /*<<< orphan*/  strm_env ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ env_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strm_value_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strm_var_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
strm_var_match(strm_state* state, strm_string name, strm_value val)
{
  if (state && state->env) {
    strm_value v0;
    if (env_get((strm_env*)state->env, name, &v0) == 0) {
      if (strm_value_eq(v0, val))
        return STRM_OK;
      return STRM_NG;
    }
  }
  return strm_var_set(state, name, val);
}