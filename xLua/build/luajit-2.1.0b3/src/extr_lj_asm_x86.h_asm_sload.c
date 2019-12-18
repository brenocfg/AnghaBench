#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_33__ {int flags; } ;
struct TYPE_31__ {scalar_t__ irt; } ;
struct TYPE_32__ {int op2; TYPE_1__ t; scalar_t__ op1; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  TYPE_1__ IRType1 ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_AE ; 
 int /*<<< orphan*/  CC_NE ; 
 int IRSLOAD_CONVERT ; 
 int IRSLOAD_FRAME ; 
 int IRSLOAD_PARENT ; 
 int IRSLOAD_TYPECHECK ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ IRT_NUM ; 
 int JIT_F_BMI2 ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_DUALNUM ; 
 int LJ_FR2 ; 
 int LJ_TISNUM ; 
 int /*<<< orphan*/  REF_BASE ; 
 int REX_64 ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int VEX_64 ; 
 int XI_O16 ; 
 int XO_ARITHi ; 
 int XO_ARITHi8 ; 
 int XO_CVTSI2SD ; 
 int XO_CVTTSD2SI ; 
 int XO_MOV ; 
 int XO_MOVSD ; 
 int XOg_CMP ; 
 int XOg_ROR ; 
 int XOg_SAR ; 
 int XOg_SHL ; 
 int XOg_SHR ; 
 int XV_RORX ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int asm_load_lightud64 (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  asm_tointg (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_3__*,int,int,int,int) ; 
 int /*<<< orphan*/  emit_rr (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  emit_shifti (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  emit_u32 (TYPE_3__*,int) ; 
 scalar_t__ irt_isaddr (TYPE_1__) ; 
 scalar_t__ irt_isguard (TYPE_1__) ; 
 scalar_t__ irt_isint (TYPE_1__) ; 
 scalar_t__ irt_isinteger (TYPE_1__) ; 
 scalar_t__ irt_islightud (TYPE_1__) ; 
 scalar_t__ irt_isnil (TYPE_1__) ; 
 scalar_t__ irt_isnum (TYPE_1__) ; 
 scalar_t__ irt_ispri (TYPE_1__) ; 
 int irt_toitype (TYPE_1__) ; 
 scalar_t__ irt_type (TYPE_1__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int ra_alloc1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_dest (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int) ; 
 int ra_scratch (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_used (TYPE_2__*) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asm_sload(ASMState *as, IRIns *ir)
{
  int32_t ofs = 8*((int32_t)ir->op1-1-LJ_FR2) +
		(!LJ_FR2 && (ir->op2 & IRSLOAD_FRAME) ? 4 : 0);
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
#if LJ_64 && !LJ_GC64
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
#if LJ_GC64
      if (irt_isaddr(t)) {
	/* LJ_GC64 type check + tag removal without BMI2 and with BMI2:
	**
	**  mov r64, [addr]    rorx r64, [addr], 47
	**  ror r64, 47
	**  cmp r16, itype     cmp r16, itype
	**  jne ->exit         jne ->exit
	**  shr r64, 16        shr r64, 16
	*/
	emit_shifti(as, XOg_SHR|REX_64, dest, 17);
	if ((ir->op2 & IRSLOAD_TYPECHECK)) {
	  asm_guardcc(as, CC_NE);
	  emit_i8(as, irt_toitype(t));
	  emit_rr(as, XO_ARITHi8, XOg_CMP, dest);
	  emit_i8(as, XI_O16);
	}
	if ((as->flags & JIT_F_BMI2)) {
	  emit_i8(as, 47);
	  emit_rmro(as, XV_RORX|VEX_64, dest, base, ofs);
	} else {
	  if ((ir->op2 & IRSLOAD_TYPECHECK))
	    emit_shifti(as, XOg_ROR|REX_64, dest, 47);
	  else
	    emit_shifti(as, XOg_SHL|REX_64, dest, 17);
	  emit_rmro(as, XO_MOV, dest|REX_64, base, ofs);
	}
	return;
      } else
#endif
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
#if LJ_GC64
      emit_u32(as, LJ_TISNUM << 15);
#else
      emit_u32(as, LJ_TISNUM);
#endif
      emit_rmro(as, XO_ARITHi, XOg_CMP, base, ofs+4);
#if LJ_GC64
    } else if (irt_isnil(t)) {
      /* LJ_GC64 type check for nil:
      **
      **   cmp qword [addr], -1
      **   jne ->exit
      */
      emit_i8(as, -1);
      emit_rmro(as, XO_ARITHi8, XOg_CMP|REX_64, base, ofs);
    } else if (irt_ispri(t)) {
      emit_u32(as, (irt_toitype(t) << 15) | 0x7fff);
      emit_rmro(as, XO_ARITHi, XOg_CMP, base, ofs+4);
    } else {
      /* LJ_GC64 type check only:
      **
      **   mov r64, [addr]
      **   sar r64, 47
      **   cmp r32, itype
      **   jne ->exit
      */
      Reg tmp = ra_scratch(as, rset_exclude(RSET_GPR, base));
      emit_i8(as, irt_toitype(t));
      emit_rr(as, XO_ARITHi8, XOg_CMP, tmp);
      emit_shifti(as, XOg_SAR|REX_64, tmp, 47);
      emit_rmro(as, XO_MOV, tmp|REX_64, base, ofs+4);
#else
    } else {
      emit_i8(as, irt_toitype(t));
      emit_rmro(as, XO_ARITHi8, XOg_CMP, base, ofs+4);
#endif
    }
  }
}