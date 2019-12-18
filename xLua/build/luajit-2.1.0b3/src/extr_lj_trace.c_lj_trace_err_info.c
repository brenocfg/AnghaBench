#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* L; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ TraceError ;
struct TYPE_5__ {int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_ERRRUN ; 
 int /*<<< orphan*/  lj_err_throw (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lj_trace_err_info(jit_State *J, TraceError e)
{
  setintV(J->L->top++, (int32_t)e);
  lj_err_throw(J->L, LUA_ERRRUN);
}