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
typedef  int /*<<< orphan*/  x86Op ;
struct TYPE_5__ {scalar_t__ o; int /*<<< orphan*/  t; int /*<<< orphan*/  op1; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
#define  IRT_FLOAT 133 
#define  IRT_I16 132 
#define  IRT_I8 131 
#define  IRT_NUM 130 
#define  IRT_U16 129 
#define  IRT_U8 128 
 scalar_t__ IR_FLOAD ; 
 int /*<<< orphan*/  LJ_64 ; 
 int /*<<< orphan*/  REX_64 ; 
 int /*<<< orphan*/  RID_MRM ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_MOVSD ; 
 int /*<<< orphan*/  XO_MOVSS ; 
 int /*<<< orphan*/  XO_MOVSXb ; 
 int /*<<< orphan*/  XO_MOVSXw ; 
 int /*<<< orphan*/  XO_MOVZXb ; 
 int /*<<< orphan*/  XO_MOVZXw ; 
 int /*<<< orphan*/  asm_fusefref (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_fusexref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mrm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_is64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isu32 (int /*<<< orphan*/ ) ; 
 int irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_dest (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_fxload(ASMState *as, IRIns *ir)
{
  Reg dest = ra_dest(as, ir, irt_isfp(ir->t) ? RSET_FPR : RSET_GPR);
  x86Op xo;
  if (ir->o == IR_FLOAD)
    asm_fusefref(as, ir, RSET_GPR);
  else
    asm_fusexref(as, ir->op1, RSET_GPR);
  /* ir->op2 is ignored -- unaligned loads are ok on x86. */
  switch (irt_type(ir->t)) {
  case IRT_I8: xo = XO_MOVSXb; break;
  case IRT_U8: xo = XO_MOVZXb; break;
  case IRT_I16: xo = XO_MOVSXw; break;
  case IRT_U16: xo = XO_MOVZXw; break;
  case IRT_NUM: xo = XO_MOVSD; break;
  case IRT_FLOAT: xo = XO_MOVSS; break;
  default:
    if (LJ_64 && irt_is64(ir->t))
      dest |= REX_64;
    else
      lua_assert(irt_isint(ir->t) || irt_isu32(ir->t) || irt_isaddr(ir->t));
    xo = XO_MOV;
    break;
  }
  emit_mrm(as, xo, dest, RID_MRM);
}