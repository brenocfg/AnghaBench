#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;
typedef  struct TYPE_21__   TYPE_18__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_19__* J; } ;
struct TYPE_25__ {int i; int /*<<< orphan*/  t; } ;
struct TYPE_23__ {int hi; int lo; } ;
struct TYPE_24__ {TYPE_1__ u32; } ;
struct TYPE_22__ {int /*<<< orphan*/  L; } ;
struct TYPE_21__ {int /*<<< orphan*/  tmptv; } ;
typedef  TYPE_2__ TValue ;
typedef  int Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_3__ IRIns ;
typedef  TYPE_4__ ASMState ;

/* Variables and functions */
 TYPE_3__* IR (int /*<<< orphan*/ ) ; 
 TYPE_18__* J2G (TYPE_19__*) ; 
 scalar_t__ LJ_64 ; 
 int REX_64 ; 
 int /*<<< orphan*/  REX_64IR (TYPE_3__*,int) ; 
 int RID_ESP ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_ARITHi ; 
 int /*<<< orphan*/  XO_LEA ; 
 int XOg_OR ; 
 int /*<<< orphan*/  emit_loada (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_movmroi (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/  emit_movtomro (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_4__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  emit_u32 (TYPE_4__*,int) ; 
 int /*<<< orphan*/ * ir_knum (TYPE_3__*) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_ispri (int /*<<< orphan*/ ) ; 
 int irt_toitype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kvalue (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*) ; 
 int ra_alloc1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_spill (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asm_tvptr(ASMState *as, Reg dest, IRRef ref)
{
  IRIns *ir = IR(ref);
  if (irt_isnum(ir->t)) {
    /* For numbers use the constant itself or a spill slot as a TValue. */
    if (irref_isk(ref))
      emit_loada(as, dest, ir_knum(ir));
    else
      emit_rmro(as, XO_LEA, dest|REX_64, RID_ESP, ra_spill(as, ir));
  } else {
    /* Otherwise use g->tmptv to hold the TValue. */
#if LJ_GC64
    if (irref_isk(ref)) {
      TValue k;
      lj_ir_kvalue(as->J->L, &k, ir);
      emit_movmroi(as, dest, 4, k.u32.hi);
      emit_movmroi(as, dest, 0, k.u32.lo);
    } else {
      /* TODO: 64 bit store + 32 bit load-modify-store is suboptimal. */
      Reg src = ra_alloc1(as, ref, rset_exclude(RSET_GPR, dest));
      if (irt_is64(ir->t)) {
	emit_u32(as, irt_toitype(ir->t) << 15);
	emit_rmro(as, XO_ARITHi, XOg_OR, dest, 4);
      } else {
	/* Currently, no caller passes integers that might end up here. */
	emit_movmroi(as, dest, 4, (irt_toitype(ir->t) << 15));
      }
      emit_movtomro(as, REX_64IR(ir, src), dest, 0);
    }
#else
    if (!irref_isk(ref)) {
      Reg src = ra_alloc1(as, ref, rset_exclude(RSET_GPR, dest));
      emit_movtomro(as, REX_64IR(ir, src), dest, 0);
    } else if (!irt_ispri(ir->t)) {
      emit_movmroi(as, dest, 0, ir->i);
    }
    if (!(LJ_64 && irt_islightud(ir->t)))
      emit_movmroi(as, dest, 4, irt_toitype(ir->t));
#endif
    emit_loada(as, dest, &J2G(as->J)->tmptv);
  }
}