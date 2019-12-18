#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  size_t int32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * fpr; scalar_t__* gpr; } ;
typedef  TYPE_2__ ExitState ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int /*<<< orphan*/ ) ; 
 size_t RID_NUM_FPR ; 
 size_t RID_NUM_GPR ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  setnanV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisnan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trace_exit_regs(lua_State *L, ExitState *ex)
{
  int32_t i;
  setintV(L->top++, RID_NUM_GPR);
  setintV(L->top++, RID_NUM_FPR);
  for (i = 0; i < RID_NUM_GPR; i++) {
    if (sizeof(ex->gpr[i]) == sizeof(int32_t))
      setintV(L->top++, (int32_t)ex->gpr[i]);
    else
      setnumV(L->top++, (lua_Number)ex->gpr[i]);
  }
#if !LJ_SOFTFP
  for (i = 0; i < RID_NUM_FPR; i++) {
    setnumV(L->top, ex->fpr[i]);
    if (LJ_UNLIKELY(tvisnan(L->top)))
      setnanV(L->top);
    L->top++;
  }
#endif
}