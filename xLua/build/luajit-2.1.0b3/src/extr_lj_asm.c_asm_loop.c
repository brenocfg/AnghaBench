#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * mcp; int /*<<< orphan*/  realign; int /*<<< orphan*/ * mcloop; scalar_t__ fuseref; scalar_t__ sectref; int /*<<< orphan*/ * invmcp; int /*<<< orphan*/  flagmcp; scalar_t__ gcsteps; int /*<<< orphan*/  snapno; int /*<<< orphan*/  loopsnapno; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  RA_DBGX (TYPE_1__*) ; 
 int /*<<< orphan*/  RA_DBG_FLUSH () ; 
 int /*<<< orphan*/  asm_gc_check (TYPE_1__*) ; 
 int /*<<< orphan*/  asm_loop_fixup (TYPE_1__*) ; 
 int /*<<< orphan*/  asm_phi_copyspill (TYPE_1__*) ; 
 int /*<<< orphan*/  asm_phi_shuffle (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_jmp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neverfuse (TYPE_1__*) ; 

__attribute__((used)) static void asm_loop(ASMState *as)
{
  MCode *mcspill;
  /* LOOP is a guard, so the snapno is up to date. */
  as->loopsnapno = as->snapno;
  if (as->gcsteps)
    asm_gc_check(as);
  /* LOOP marks the transition from the variant to the invariant part. */
  as->flagmcp = as->invmcp = NULL;
  as->sectref = 0;
  if (!neverfuse(as)) as->fuseref = 0;
  asm_phi_shuffle(as);
  mcspill = as->mcp;
  asm_phi_copyspill(as);
  asm_loop_fixup(as);
  as->mcloop = as->mcp;
  RA_DBGX((as, "===== LOOP ====="));
  if (!as->realign) RA_DBG_FLUSH();
  if (as->mcp != mcspill)
    emit_jmp(as, mcspill);
}