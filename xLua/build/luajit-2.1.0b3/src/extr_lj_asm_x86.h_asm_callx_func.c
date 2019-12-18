#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
struct TYPE_10__ {scalar_t__ u64; } ;
struct TYPE_9__ {void* mcp; } ;
struct TYPE_8__ {scalar_t__ o; scalar_t__ i; } ;
typedef  void MCode ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ IR_KINT64 ; 
 int /*<<< orphan*/  UNUSED (TYPE_2__*) ; 
 TYPE_3__* ir_k64 (TYPE_1__*) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *asm_callx_func(ASMState *as, IRIns *irf, IRRef func)
{
#if LJ_32
  UNUSED(as);
  if (irref_isk(func))
    return (void *)irf->i;
#else
  if (irref_isk(func)) {
    MCode *p;
    if (irf->o == IR_KINT64)
      p = (MCode *)(void *)ir_k64(irf)->u64;
    else
      p = (MCode *)(void *)(uintptr_t)(uint32_t)irf->i;
    if (p - as->mcp == (int32_t)(p - as->mcp))
      return p;  /* Call target is still in +-2GB range. */
    /* Avoid the indirect case of emit_call(). Try to hoist func addr. */
  }
#endif
  return NULL;
}