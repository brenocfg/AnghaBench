#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_29__ {int* snapmap; } ;
struct TYPE_28__ {TYPE_1__* J; TYPE_8__* T; } ;
struct TYPE_27__ {int i; int /*<<< orphan*/  t; } ;
struct TYPE_26__ {size_t mapofs; size_t nent; } ;
struct TYPE_24__ {int hi; int lo; } ;
struct TYPE_25__ {TYPE_2__ u32; } ;
struct TYPE_23__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_3__ TValue ;
typedef  TYPE_4__ SnapShot ;
typedef  int SnapEntry ;
typedef  int /*<<< orphan*/  Reg ;
typedef  size_t MSize ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_5__ IRIns ;
typedef  scalar_t__ BCReg ;
typedef  TYPE_6__ ASMState ;

/* Variables and functions */
 TYPE_5__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_DUALNUM ; 
 int LJ_FR2 ; 
 int LJ_TISNUM ; 
 int /*<<< orphan*/  REX_64 ; 
 int /*<<< orphan*/  REX_64IR (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_BASE ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int SNAP_CONT ; 
 int SNAP_FRAME ; 
 int SNAP_NORESTORE ; 
 int /*<<< orphan*/  XO_ARITHi ; 
 int /*<<< orphan*/  XO_MOVSDto ; 
 int /*<<< orphan*/  XO_MOVmi ; 
 int /*<<< orphan*/  XOg_OR ; 
 int /*<<< orphan*/  checkmclim (TYPE_6__*) ; 
 int /*<<< orphan*/  emit_i32 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  emit_movmroi (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_movtomro (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_u32 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  irref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 int irt_toitype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kvalue (int /*<<< orphan*/ ,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snap_nextofs (TYPE_8__*,TYPE_4__*) ; 
 int /*<<< orphan*/  snap_ref (int) ; 
 scalar_t__ snap_slot (int) ; 
 scalar_t__ tvisnil (TYPE_3__*) ; 

__attribute__((used)) static void asm_stack_restore(ASMState *as, SnapShot *snap)
{
  SnapEntry *map = &as->T->snapmap[snap->mapofs];
#if !LJ_FR2 || defined(LUA_USE_ASSERT)
  SnapEntry *flinks = &as->T->snapmap[snap_nextofs(as->T, snap)-1-LJ_FR2];
#endif
  MSize n, nent = snap->nent;
  /* Store the value of all modified slots to the Lua stack. */
  for (n = 0; n < nent; n++) {
    SnapEntry sn = map[n];
    BCReg s = snap_slot(sn);
    int32_t ofs = 8*((int32_t)s-1-LJ_FR2);
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
#if LJ_GC64
	if (irt_is64(ir->t)) {
	  /* TODO: 64 bit store + 32 bit load-modify-store is suboptimal. */
	  emit_u32(as, irt_toitype(ir->t) << 15);
	  emit_rmro(as, XO_ARITHi, XOg_OR, RID_BASE, ofs+4);
	} else if (LJ_DUALNUM && irt_isinteger(ir->t)) {
	  emit_movmroi(as, RID_BASE, ofs+4, LJ_TISNUM << 15);
	} else {
	  emit_movmroi(as, RID_BASE, ofs+4, (irt_toitype(ir->t)<<15)|0x7fff);
	}
#endif
	emit_movtomro(as, REX_64IR(ir, src), RID_BASE, ofs);
#if LJ_GC64
      } else {
	TValue k;
	lj_ir_kvalue(as->J->L, &k, ir);
	if (tvisnil(&k)) {
	  emit_i32(as, -1);
	  emit_rmro(as, XO_MOVmi, REX_64, RID_BASE, ofs);
	} else {
	  emit_movmroi(as, RID_BASE, ofs+4, k.u32.hi);
	  emit_movmroi(as, RID_BASE, ofs, k.u32.lo);
	}
#else
      } else if (!irt_ispri(ir->t)) {
	emit_movmroi(as, RID_BASE, ofs, ir->i);
#endif
      }
      if ((sn & (SNAP_CONT|SNAP_FRAME))) {
#if !LJ_FR2
	if (s != 0)  /* Do not overwrite link to previous frame. */
	  emit_movmroi(as, RID_BASE, ofs+4, (int32_t)(*flinks--));
#endif
#if !LJ_GC64
      } else {
	if (!(LJ_64 && irt_islightud(ir->t)))
	  emit_movmroi(as, RID_BASE, ofs+4, irt_toitype(ir->t));
#endif
      }
    }
    checkmclim(as);
  }
  lua_assert(map + nent == flinks);
}