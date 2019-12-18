#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {scalar_t__ base; int ofs; } ;
struct TYPE_7__ {int loopinv; TYPE_1__ mrm; scalar_t__ realign; int /*<<< orphan*/ * invmcp; int /*<<< orphan*/ * mcp; int /*<<< orphan*/  snapno; int /*<<< orphan*/  J; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ LJ_GC64 ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 scalar_t__ RID_RIP ; 
 int /*<<< orphan*/  emit_jcc (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_sjcc (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * exitstub_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmprel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asm_guardcc(ASMState *as, int cc)
{
  MCode *target = exitstub_addr(as->J, as->snapno);
  MCode *p = as->mcp;
  if (LJ_UNLIKELY(p == as->invmcp)) {
    as->loopinv = 1;
    *(int32_t *)(p+1) = jmprel(p+5, target);
    target = p;
    cc ^= 1;
    if (as->realign) {
      if (LJ_GC64 && LJ_UNLIKELY(as->mrm.base == RID_RIP))
	as->mrm.ofs += 2;  /* Fixup RIP offset for pending fused load. */
      emit_sjcc(as, cc, target);
      return;
    }
  }
  if (LJ_GC64 && LJ_UNLIKELY(as->mrm.base == RID_RIP))
    as->mrm.ofs += 6;  /* Fixup RIP offset for pending fused load. */
  emit_jcc(as, cc, target);
}