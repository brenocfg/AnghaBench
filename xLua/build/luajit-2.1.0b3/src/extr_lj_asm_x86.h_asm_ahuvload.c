#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int ofs; } ;
struct TYPE_21__ {int flags; TYPE_1__ mrm; } ;
struct TYPE_20__ {int /*<<< orphan*/  t; int /*<<< orphan*/  op1; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_AE ; 
 int /*<<< orphan*/  CC_NE ; 
 scalar_t__ IRT_NUM ; 
 int JIT_F_BMI2 ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_DUALNUM ; 
 int LJ_TISNUM ; 
 int REX_64 ; 
 int RID_MAX_GPR ; 
 int RID_MRM ; 
 int RID_NONE ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int VEX_64 ; 
 int XI_O16 ; 
 int XO_ARITHi ; 
 int XO_ARITHi8 ; 
 int XO_MOV ; 
 int XO_MOVSD ; 
 int XOg_CMP ; 
 int XOg_ROR ; 
 int XOg_SAR ; 
 int XOg_SHR ; 
 int XV_RORX ; 
 int /*<<< orphan*/  asm_fuseahuref (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int asm_load_lightud64 (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  emit_rr (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  emit_shifti (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  emit_u32 (TYPE_3__*,int) ; 
 scalar_t__ irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnil (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 int irt_toitype (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int ra_dest (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int) ; 
 int ra_scratch (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_used (TYPE_2__*) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asm_ahuvload(ASMState *as, IRIns *ir)
{
#if LJ_GC64
  Reg tmp = RID_NONE;
#endif
  lua_assert(irt_isnum(ir->t) || irt_ispri(ir->t) || irt_isaddr(ir->t) ||
	     (LJ_DUALNUM && irt_isint(ir->t)));
#if LJ_64 && !LJ_GC64
  if (irt_islightud(ir->t)) {
    Reg dest = asm_load_lightud64(as, ir, 1);
    if (ra_hasreg(dest)) {
      asm_fuseahuref(as, ir->op1, RSET_GPR);
      emit_mrm(as, XO_MOV, dest|REX_64, RID_MRM);
    }
    return;
  } else
#endif
  if (ra_used(ir)) {
    RegSet allow = irt_isnum(ir->t) ? RSET_FPR : RSET_GPR;
    Reg dest = ra_dest(as, ir, allow);
    asm_fuseahuref(as, ir->op1, RSET_GPR);
#if LJ_GC64
    if (irt_isaddr(ir->t)) {
      emit_shifti(as, XOg_SHR|REX_64, dest, 17);
      asm_guardcc(as, CC_NE);
      emit_i8(as, irt_toitype(ir->t));
      emit_rr(as, XO_ARITHi8, XOg_CMP, dest);
      emit_i8(as, XI_O16);
      if ((as->flags & JIT_F_BMI2)) {
	emit_i8(as, 47);
	emit_mrm(as, XV_RORX|VEX_64, dest, RID_MRM);
      } else {
	emit_shifti(as, XOg_ROR|REX_64, dest, 47);
	emit_mrm(as, XO_MOV, dest|REX_64, RID_MRM);
      }
      return;
    } else
#endif
    emit_mrm(as, dest < RID_MAX_GPR ? XO_MOV : XO_MOVSD, dest, RID_MRM);
  } else {
    RegSet gpr = RSET_GPR;
#if LJ_GC64
    if (irt_isaddr(ir->t)) {
      tmp = ra_scratch(as, RSET_GPR);
      gpr = rset_exclude(gpr, tmp);
    }
#endif
    asm_fuseahuref(as, ir->op1, gpr);
  }
  /* Always do the type check, even if the load result is unused. */
  as->mrm.ofs += 4;
  asm_guardcc(as, irt_isnum(ir->t) ? CC_AE : CC_NE);
  if (LJ_64 && irt_type(ir->t) >= IRT_NUM) {
    lua_assert(irt_isinteger(ir->t) || irt_isnum(ir->t));
#if LJ_GC64
    emit_u32(as, LJ_TISNUM << 15);
#else
    emit_u32(as, LJ_TISNUM);
#endif
    emit_mrm(as, XO_ARITHi, XOg_CMP, RID_MRM);
#if LJ_GC64
  } else if (irt_isaddr(ir->t)) {
    as->mrm.ofs -= 4;
    emit_i8(as, irt_toitype(ir->t));
    emit_mrm(as, XO_ARITHi8, XOg_CMP, tmp);
    emit_shifti(as, XOg_SAR|REX_64, tmp, 47);
    emit_mrm(as, XO_MOV, tmp|REX_64, RID_MRM);
  } else if (irt_isnil(ir->t)) {
    as->mrm.ofs -= 4;
    emit_i8(as, -1);
    emit_mrm(as, XO_ARITHi8, XOg_CMP|REX_64, RID_MRM);
  } else {
    emit_u32(as, (irt_toitype(ir->t) << 15) | 0x7fff);
    emit_mrm(as, XO_ARITHi, XOg_CMP, RID_MRM);
#else
  } else {
    emit_i8(as, irt_toitype(ir->t));
    emit_mrm(as, XO_ARITHi8, XOg_CMP, RID_MRM);
#endif
  }
}