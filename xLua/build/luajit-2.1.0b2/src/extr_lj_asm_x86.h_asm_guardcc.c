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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int loopinv; scalar_t__ realign; int /*<<< orphan*/ * invmcp; int /*<<< orphan*/ * mcp; int /*<<< orphan*/  snapno; int /*<<< orphan*/  J; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int) ; 
 int /*<<< orphan*/  emit_jcc (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_sjcc (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
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
      emit_sjcc(as, cc, target);
      return;
    }
  }
  emit_jcc(as, cc, target);
}