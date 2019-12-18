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

/* Type definitions */
typedef  int int32_t ;
struct TYPE_16__ {scalar_t__ irt; } ;
struct TYPE_17__ {int op2; TYPE_1__ t; scalar_t__ op1; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  TYPE_1__ IRType1 ;
typedef  TYPE_2__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_AE ; 
 int /*<<< orphan*/  CC_NE ; 
 int IRSLOAD_CONVERT ; 
 int IRSLOAD_FRAME ; 
 int IRSLOAD_PARENT ; 
 int IRSLOAD_TYPECHECK ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ IRT_NUM ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  LJ_TISNUM ; 
 int /*<<< orphan*/  REF_BASE ; 
 int REX_64 ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_ARITHi ; 
 int /*<<< orphan*/  XO_ARITHi8 ; 
 int /*<<< orphan*/  XO_CVTSI2SD ; 
 int /*<<< orphan*/  XO_CVTTSD2SI ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_MOVSD ; 
 int XOg_CMP ; 
 int /*<<< orphan*/  asm_guardcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int asm_load_lightud64 (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  asm_tointg (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  emit_i8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rmro (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  emit_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isaddr (TYPE_1__) ; 
 scalar_t__ irt_isguard (TYPE_1__) ; 
 scalar_t__ irt_isint (TYPE_1__) ; 
 scalar_t__ irt_isinteger (TYPE_1__) ; 
 scalar_t__ irt_islightud (TYPE_1__) ; 
 scalar_t__ irt_isnum (TYPE_1__) ; 
 int /*<<< orphan*/  irt_toitype (TYPE_1__) ; 
 scalar_t__ irt_type (TYPE_1__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int ra_alloc1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_dest (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int) ; 
 int ra_scratch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_used (TYPE_2__*) ; 

__attribute__((used)) static void asm_sload(ASMState *as, IRIns *ir)
{
  int32_t ofs = 8*((int32_t)ir->op1-1) + ((ir->op2 & IRSLOAD_FRAME) ? 4 : 0);
  IRType1 t = ir->t;
  Reg base;
  lua_assert(!(ir->op2 & IRSLOAD_PARENT));  /* Handled by asm_head_side(). */
  lua_assert(irt_isguard(t) || !(ir->op2 & IRSLOAD_TYPECHECK));
  lua_assert(LJ_DUALNUM ||
	     !irt_isint(t) || (ir->op2 & (IRSLOAD_CONVERT|IRSLOAD_FRAME)));
  if ((ir->op2 & IRSLOAD_CONVERT) && irt_isguard(t) && irt_isint(t)) {
    Reg left = ra_scratch(as, RSET_FPR);
    asm_tointg(as, ir, left);  /* Frees dest reg. Do this before base alloc. */
    base = ra_alloc1(as, REF_BASE, RSET_GPR);
    emit_rmro(as, XO_MOVSD, left, base, ofs);
    t.irt = IRT_NUM;  /* Continue with a regular number type check. */
#if LJ_64
  } else if (irt_islightud(t)) {
    Reg dest = asm_load_lightud64(as, ir, (ir->op2 & IRSLOAD_TYPECHECK));
    if (ra_hasreg(dest)) {
      base = ra_alloc1(as, REF_BASE, RSET_GPR);
      emit_rmro(as, XO_MOV, dest|REX_64, base, ofs);
    }
    return;
#endif
  } else if (ra_used(ir)) {
    RegSet allow = irt_isnum(t) ? RSET_FPR : RSET_GPR;
    Reg dest = ra_dest(as, ir, allow);
    base = ra_alloc1(as, REF_BASE, RSET_GPR);
    lua_assert(irt_isnum(t) || irt_isint(t) || irt_isaddr(t));
    if ((ir->op2 & IRSLOAD_CONVERT)) {
      t.irt = irt_isint(t) ? IRT_NUM : IRT_INT;  /* Check for original type. */
      emit_rmro(as, irt_isint(t) ? XO_CVTSI2SD : XO_CVTTSD2SI, dest, base, ofs);
    } else {
      emit_rmro(as, irt_isnum(t) ? XO_MOVSD : XO_MOV, dest, base, ofs);
    }
  } else {
    if (!(ir->op2 & IRSLOAD_TYPECHECK))
      return;  /* No type check: avoid base alloc. */
    base = ra_alloc1(as, REF_BASE, RSET_GPR);
  }
  if ((ir->op2 & IRSLOAD_TYPECHECK)) {
    /* Need type check, even if the load result is unused. */
    asm_guardcc(as, irt_isnum(t) ? CC_AE : CC_NE);
    if (LJ_64 && irt_type(t) >= IRT_NUM) {
      lua_assert(irt_isinteger(t) || irt_isnum(t));
      emit_u32(as, LJ_TISNUM);
      emit_rmro(as, XO_ARITHi, XOg_CMP, base, ofs+4);
    } else {
      emit_i8(as, irt_toitype(t));
      emit_rmro(as, XO_ARITHi8, XOg_CMP, base, ofs+4);
    }
  }
}