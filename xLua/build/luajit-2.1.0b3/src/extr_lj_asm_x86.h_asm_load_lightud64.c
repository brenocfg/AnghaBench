#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Reg ;
typedef  int /*<<< orphan*/  IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NE ; 
 int REX_64 ; 
 int RID_NONE ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_ARITHi8 ; 
 int /*<<< orphan*/  XO_MOV ; 
 int XOg_CMP ; 
 int XOg_SAR ; 
 int /*<<< orphan*/  asm_guardcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_shifti (int /*<<< orphan*/ *,int,int,int) ; 
 int ra_dest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ra_scratch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Reg asm_load_lightud64(ASMState *as, IRIns *ir, int typecheck)
{
  if (ra_used(ir) || typecheck) {
    Reg dest = ra_dest(as, ir, RSET_GPR);
    if (typecheck) {
      Reg tmp = ra_scratch(as, rset_exclude(RSET_GPR, dest));
      asm_guardcc(as, CC_NE);
      emit_i8(as, -2);
      emit_rr(as, XO_ARITHi8, XOg_CMP, tmp);
      emit_shifti(as, XOg_SAR|REX_64, tmp, 47);
      emit_rr(as, XO_MOV, tmp|REX_64, dest);
    }
    return dest;
  } else {
    return RID_NONE;
  }
}