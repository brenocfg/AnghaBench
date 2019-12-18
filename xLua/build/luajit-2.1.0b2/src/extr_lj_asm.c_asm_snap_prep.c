#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ curins; scalar_t__ snapref; size_t snapno; scalar_t__ snaprename; TYPE_2__* T; } ;
struct TYPE_11__ {scalar_t__ op2; int /*<<< orphan*/  op1; } ;
struct TYPE_10__ {scalar_t__ nins; TYPE_1__* snap; } ;
struct TYPE_9__ {scalar_t__ ref; } ;
typedef  TYPE_3__ IRIns ;
typedef  TYPE_4__ ASMState ;

/* Variables and functions */
 TYPE_3__* IR (scalar_t__) ; 
 scalar_t__ REF_BIAS ; 
 int /*<<< orphan*/  asm_snap_alloc (TYPE_4__*) ; 
 scalar_t__ asm_snap_checkrename (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_snap_prep(ASMState *as)
{
  if (as->curins < as->snapref) {
    do {
      if (as->snapno == 0) return;  /* Called by sunk stores before snap #0. */
      as->snapno--;
      as->snapref = as->T->snap[as->snapno].ref;
    } while (as->curins < as->snapref);
    asm_snap_alloc(as);
    as->snaprename = as->T->nins;
  } else {
    /* Process any renames above the highwater mark. */
    for (; as->snaprename < as->T->nins; as->snaprename++) {
      IRIns *ir = IR(as->snaprename);
      if (asm_snap_checkrename(as, ir->op1))
	ir->op2 = REF_BIAS-1;  /* Kill rename. */
    }
  }
}