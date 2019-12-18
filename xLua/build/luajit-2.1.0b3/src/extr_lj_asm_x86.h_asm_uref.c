#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  v; } ;
struct TYPE_13__ {TYPE_1__ uv; } ;
struct TYPE_10__ {int /*<<< orphan*/ * uvptr; } ;
struct TYPE_12__ {TYPE_2__ l; } ;
struct TYPE_11__ {int op2; scalar_t__ o; int /*<<< orphan*/  op1; } ;
typedef  int Reg ;
typedef  int /*<<< orphan*/  MRef ;
typedef  TYPE_3__ IRIns ;
typedef  TYPE_4__ GCfunc ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NE ; 
 int /*<<< orphan*/  GCfuncL ; 
 int /*<<< orphan*/  GCupval ; 
 int /*<<< orphan*/  IR (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_UREFC ; 
 int REX_GC64 ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_ARITHib ; 
 int /*<<< orphan*/  XO_LEA ; 
 int /*<<< orphan*/  XO_MOV ; 
 int XOg_CMP ; 
 int /*<<< orphan*/  asm_guardcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closed ; 
 int /*<<< orphan*/  emit_i8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_rma (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_rmro (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_7__* gcref (int /*<<< orphan*/ ) ; 
 TYPE_4__* ir_kfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_alloc1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_dest (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ra_scratch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv ; 
 int /*<<< orphan*/  uvptr ; 
 int /*<<< orphan*/  v ; 

__attribute__((used)) static void asm_uref(ASMState *as, IRIns *ir)
{
  Reg dest = ra_dest(as, ir, RSET_GPR);
  if (irref_isk(ir->op1)) {
    GCfunc *fn = ir_kfunc(IR(ir->op1));
    MRef *v = &gcref(fn->l.uvptr[(ir->op2 >> 8)])->uv.v;
    emit_rma(as, XO_MOV, dest|REX_GC64, v);
  } else {
    Reg uv = ra_scratch(as, RSET_GPR);
    Reg func = ra_alloc1(as, ir->op1, RSET_GPR);
    if (ir->o == IR_UREFC) {
      emit_rmro(as, XO_LEA, dest|REX_GC64, uv, offsetof(GCupval, tv));
      asm_guardcc(as, CC_NE);
      emit_i8(as, 1);
      emit_rmro(as, XO_ARITHib, XOg_CMP, uv, offsetof(GCupval, closed));
    } else {
      emit_rmro(as, XO_MOV, dest|REX_GC64, uv, offsetof(GCupval, v));
    }
    emit_rmro(as, XO_MOV, uv|REX_GC64, func,
	      (int32_t)offsetof(GCfuncL, uvptr) +
	      (int32_t)sizeof(MRef) * (int32_t)(ir->op2 >> 8));
  }
}