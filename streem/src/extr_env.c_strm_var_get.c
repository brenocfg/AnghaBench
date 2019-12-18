#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
struct TYPE_3__ {struct TYPE_3__* prev; scalar_t__ env; } ;
typedef  TYPE_1__ strm_state ;
typedef  int /*<<< orphan*/  strm_env ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int env_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * globals ; 

int
strm_var_get(strm_state* state, strm_string name, strm_value* val)
{
  while (state) {
    if (state->env) {
      if (env_get((strm_env*)state->env, name, val) == 0)
        return STRM_OK;
    }
    state = state->prev;
  }
  if (!globals) return STRM_NG;
  return env_get(globals, name, val);
}