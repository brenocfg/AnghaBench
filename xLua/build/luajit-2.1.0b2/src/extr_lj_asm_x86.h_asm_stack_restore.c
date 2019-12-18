#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_18__ {int* snapmap; } ;
struct TYPE_17__ {TYPE_4__* T; } ;
struct TYPE_16__ {int i; int /*<<< orphan*/  t; } ;
struct TYPE_15__ {size_t mapofs; size_t nent; } ;
typedef  TYPE_1__ SnapShot ;
typedef  int SnapEntry ;
typedef  int /*<<< orphan*/  Reg ;
typedef  size_t MSize ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  scalar_t__ BCReg ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  REX_64IR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_BASE ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int SNAP_CONT ; 
 int SNAP_FRAME ; 
 int SNAP_NORESTORE ; 
 int /*<<< orphan*/  XO_MOVSDto ; 
 int /*<<< orphan*/  checkmclim (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_movmroi (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_movtomro (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 int irt_toitype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snap_nextofs (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  snap_ref (int) ; 
 scalar_t__ snap_slot (int) ; 

__attribute__((used)) static void asm_stack_restore(ASMState *as, SnapShot *snap)
{
  SnapEntry *map = &as->T->snapmap[snap->mapofs];
  SnapEntry *flinks = &as->T->snapmap[snap_nextofs(as->T, snap)-1];
  MSize n, nent = snap->nent;
  /* Store the value of all modified slots to the Lua stack. */
  for (n = 0; n < nent; n++) {
    SnapEntry sn = map[n];
    BCReg s = snap_slot(sn);
    int32_t ofs = 8*((int32_t)s-1);
    IRRef ref = snap_ref(sn);
    IRIns *ir = IR(ref);
    if ((sn & SNAP_NORESTORE))
      continue;
    if (irt_isnum(ir->t)) {
      Reg src = ra_alloc1(as, ref, RSET_FPR);
      emit_rmro(as, XO_MOVSDto, src, RID_BASE, ofs);
    } else {
      lua_assert(irt_ispri(ir->t) || irt_isaddr(ir->t) ||
		 (LJ_DUALNUM && irt_isinteger(ir->t)));
      if (!irref_isk(ref)) {
	Reg src = ra_alloc1(as, ref, rset_exclude(RSET_GPR, RID_BASE));
	emit_movtomro(as, REX_64IR(ir, src), RID_BASE, ofs);
      } else if (!irt_ispri(ir->t)) {
	emit_movmroi(as, RID_BASE, ofs, ir->i);
      }
      if ((sn & (SNAP_CONT|SNAP_FRAME))) {
	if (s != 0)  /* Do not overwrite link to previous frame. */
	  emit_movmroi(as, RID_BASE, ofs+4, (int32_t)(*flinks--));
      } else {
	if (!(LJ_64 && irt_islightud(ir->t)))
	  emit_movmroi(as, RID_BASE, ofs+4, irt_toitype(ir->t));
      }
    }
    checkmclim(as);
  }
  lua_assert(map + nent == flinks);
}