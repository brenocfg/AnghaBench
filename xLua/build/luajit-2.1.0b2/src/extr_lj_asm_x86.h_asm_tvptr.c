#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  J; } ;
struct TYPE_16__ {int /*<<< orphan*/  t; int /*<<< orphan*/  i; } ;
struct TYPE_15__ {int /*<<< orphan*/  tmptv; } ;
typedef  int Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 TYPE_13__* J2G (int /*<<< orphan*/ ) ; 
 scalar_t__ LJ_64 ; 
 int REX_64 ; 
 int /*<<< orphan*/  REX_64IR (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RID_ESP ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_LEA ; 
 int /*<<< orphan*/  emit_loada (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_movmroi (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movtomro (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ir_knum (TYPE_1__*) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_toitype (int /*<<< orphan*/ ) ; 
 int ra_alloc1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_spill (TYPE_2__*,TYPE_1__*) ; 
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
    if (!irref_isk(ref)) {
      Reg src = ra_alloc1(as, ref, rset_exclude(RSET_GPR, dest));
      emit_movtomro(as, REX_64IR(ir, src), dest, 0);
    } else if (!irt_ispri(ir->t)) {
      emit_movmroi(as, dest, 0, ir->i);
    }
    if (!(LJ_64 && irt_islightud(ir->t)))
      emit_movmroi(as, dest, 4, irt_toitype(ir->t));
    emit_loada(as, dest, &J2G(as->J)->tmptv);
  }
}