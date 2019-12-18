#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mcp; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  RID_RET ; 
 int /*<<< orphan*/  XI_CALL ; 
 int /*<<< orphan*/  XO_GROUP5 ; 
 int /*<<< orphan*/  XOg_CALL ; 
 int /*<<< orphan*/  emit_loadu64 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jmprel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emit_call_(ASMState *as, MCode *target)
{
  MCode *p = as->mcp;
#if LJ_64
  if (target-p != (int32_t)(target-p)) {
    /* Assumes RID_RET is never an argument to calls and always clobbered. */
    emit_rr(as, XO_GROUP5, XOg_CALL, RID_RET);
    emit_loadu64(as, RID_RET, (uint64_t)target);
    return;
  }
#endif
  *(int32_t *)(p-4) = jmprel(p, target);
  p[-5] = XI_CALL;
  as->mcp = p - 5;
}