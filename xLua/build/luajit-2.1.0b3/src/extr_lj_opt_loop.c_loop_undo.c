#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  size_t ptrdiff_t ;
struct TYPE_11__ {scalar_t__ irt; } ;
struct TYPE_10__ {int nsnap; scalar_t__ nsnapmap; TYPE_4__* snap; int /*<<< orphan*/ * snapmap; } ;
struct TYPE_12__ {TYPE_6__* bpropcache; TYPE_2__ guardemit; TYPE_1__ cur; } ;
typedef  TYPE_3__ jit_State ;
struct TYPE_15__ {scalar_t__ val; scalar_t__ key; } ;
struct TYPE_14__ {int /*<<< orphan*/  t; } ;
struct TYPE_13__ {size_t mapofs; size_t nent; } ;
typedef  TYPE_4__ SnapShot ;
typedef  int SnapNo ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  scalar_t__ MSize ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_5__ IRIns ;
typedef  TYPE_6__ BPropEntry ;

/* Variables and functions */
 size_t BPROP_SLOTS ; 
 TYPE_5__* IR (scalar_t__) ; 
 scalar_t__ REF_FIRST ; 
 int /*<<< orphan*/  irt_clearmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_clearphi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_rollback (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void loop_undo(jit_State *J, IRRef ins, SnapNo nsnap, MSize nsnapmap)
{
  ptrdiff_t i;
  SnapShot *snap = &J->cur.snap[nsnap-1];
  SnapEntry *map = J->cur.snapmap;
  map[snap->mapofs + snap->nent] = map[J->cur.snap[0].nent];  /* Restore PC. */
  J->cur.nsnapmap = (uint16_t)nsnapmap;
  J->cur.nsnap = nsnap;
  J->guardemit.irt = 0;
  lj_ir_rollback(J, ins);
  for (i = 0; i < BPROP_SLOTS; i++) {  /* Remove backprop. cache entries. */
    BPropEntry *bp = &J->bpropcache[i];
    if (bp->val >= ins)
      bp->key = 0;
  }
  for (ins--; ins >= REF_FIRST; ins--) {  /* Remove flags. */
    IRIns *ir = IR(ins);
    irt_clearphi(ir->t);
    irt_clearmark(ir->t);
  }
}