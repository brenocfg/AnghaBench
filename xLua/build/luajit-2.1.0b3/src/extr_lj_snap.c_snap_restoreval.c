#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  lua_Number ;
struct TYPE_18__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_22__ {void** gpr; int /*<<< orphan*/ * fpr; int /*<<< orphan*/ * spill; } ;
struct TYPE_21__ {TYPE_3__* ir; } ;
struct TYPE_20__ {scalar_t__ o; scalar_t__ op2; size_t op1; int /*<<< orphan*/  prev; int /*<<< orphan*/  t; } ;
struct TYPE_19__ {void* u64; } ;
typedef  TYPE_2__ TValue ;
typedef  int /*<<< orphan*/  SnapNo ;
typedef  int /*<<< orphan*/  RegSP ;
typedef  size_t Reg ;
typedef  int /*<<< orphan*/  IRType1 ;
typedef  size_t IRRef ;
typedef  TYPE_3__ IRIns ;
typedef  TYPE_4__ GCtrace ;
typedef  int /*<<< orphan*/  GCobj ;
typedef  scalar_t__ GCSize ;
typedef  TYPE_5__ ExitState ;
typedef  int /*<<< orphan*/  BloomFilter ;

/* Variables and functions */
 scalar_t__ IRCONV_NUM_INT ; 
 scalar_t__ IR_CONV ; 
 scalar_t__ LJ_DUALNUM ; 
 scalar_t__ LJ_UNLIKELY (int /*<<< orphan*/ ) ; 
 size_t RID_MIN_FPR ; 
 size_t RID_MIN_GPR ; 
 int /*<<< orphan*/  bloomtest (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ intV (TYPE_2__*) ; 
 scalar_t__ irref_isk (size_t) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_toitype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kvalue (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ ra_hasspill (size_t) ; 
 scalar_t__ ra_noreg (size_t) ; 
 size_t regsp_reg (int /*<<< orphan*/ ) ; 
 size_t regsp_spill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcV (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setintV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnumV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpriV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snap_renameref (TYPE_4__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snap_restoreval(jit_State *J, GCtrace *T, ExitState *ex,
			    SnapNo snapno, BloomFilter rfilt,
			    IRRef ref, TValue *o)
{
  IRIns *ir = &T->ir[ref];
  IRType1 t = ir->t;
  RegSP rs = ir->prev;
  if (irref_isk(ref)) {  /* Restore constant slot. */
    lj_ir_kvalue(J->L, o, ir);
    return;
  }
  if (LJ_UNLIKELY(bloomtest(rfilt, ref)))
    rs = snap_renameref(T, snapno, ref, rs);
  if (ra_hasspill(regsp_spill(rs))) {  /* Restore from spill slot. */
    int32_t *sps = &ex->spill[regsp_spill(rs)];
    if (irt_isinteger(t)) {
      setintV(o, *sps);
#if !LJ_SOFTFP
    } else if (irt_isnum(t)) {
      o->u64 = *(uint64_t *)sps;
#endif
#if LJ_64 && !LJ_GC64
    } else if (irt_islightud(t)) {
      /* 64 bit lightuserdata which may escape already has the tag bits. */
      o->u64 = *(uint64_t *)sps;
#endif
    } else {
      lua_assert(!irt_ispri(t));  /* PRI refs never have a spill slot. */
      setgcV(J->L, o, (GCobj *)(uintptr_t)*(GCSize *)sps, irt_toitype(t));
    }
  } else {  /* Restore from register. */
    Reg r = regsp_reg(rs);
    if (ra_noreg(r)) {
      lua_assert(ir->o == IR_CONV && ir->op2 == IRCONV_NUM_INT);
      snap_restoreval(J, T, ex, snapno, rfilt, ir->op1, o);
      if (LJ_DUALNUM) setnumV(o, (lua_Number)intV(o));
      return;
    } else if (irt_isinteger(t)) {
      setintV(o, (int32_t)ex->gpr[r-RID_MIN_GPR]);
#if !LJ_SOFTFP
    } else if (irt_isnum(t)) {
      setnumV(o, ex->fpr[r-RID_MIN_FPR]);
#endif
#if LJ_64 && !LJ_GC64
    } else if (irt_is64(t)) {
      /* 64 bit values that already have the tag bits. */
      o->u64 = ex->gpr[r-RID_MIN_GPR];
#endif
    } else if (irt_ispri(t)) {
      setpriV(o, irt_toitype(t));
    } else {
      setgcV(J->L, o, (GCobj *)ex->gpr[r-RID_MIN_GPR], irt_toitype(t));
    }
  }
}