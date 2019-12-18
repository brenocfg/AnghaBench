#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int ofs; } ;
struct TYPE_18__ {TYPE_1__ mrm; } ;
struct TYPE_17__ {int /*<<< orphan*/  t; int /*<<< orphan*/  op1; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_AE ; 
 int /*<<< orphan*/  CC_NE ; 
 scalar_t__ IRT_NUM ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  LJ_TISNUM ; 
 int REX_64 ; 
 int RID_MAX_GPR ; 
 int /*<<< orphan*/  RID_MRM ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_ARITHi ; 
 int /*<<< orphan*/  XO_ARITHi8 ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_MOVSD ; 
 int XOg_CMP ; 
 int /*<<< orphan*/  asm_fuseahuref (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int asm_load_lightud64 (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_u32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_islightud (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_toitype (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int ra_dest (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int) ; 
 scalar_t__ ra_used (TYPE_2__*) ; 

__attribute__((used)) static void asm_ahuvload(ASMState *as, IRIns *ir)
{
  lua_assert(irt_isnum(ir->t) || irt_ispri(ir->t) || irt_isaddr(ir->t) ||
	     (LJ_DUALNUM && irt_isint(ir->t)));
#if LJ_64
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
    emit_mrm(as, dest < RID_MAX_GPR ? XO_MOV : XO_MOVSD, dest, RID_MRM);
  } else {
    asm_fuseahuref(as, ir->op1, RSET_GPR);
  }
  /* Always do the type check, even if the load result is unused. */
  as->mrm.ofs += 4;
  asm_guardcc(as, irt_isnum(ir->t) ? CC_AE : CC_NE);
  if (LJ_64 && irt_type(ir->t) >= IRT_NUM) {
    lua_assert(irt_isinteger(ir->t) || irt_isnum(ir->t));
    emit_u32(as, LJ_TISNUM);
    emit_mrm(as, XO_ARITHi, XOg_CMP, RID_MRM);
  } else {
    emit_i8(as, irt_toitype(ir->t));
    emit_mrm(as, XO_ARITHi8, XOg_CMP, RID_MRM);
  }
}