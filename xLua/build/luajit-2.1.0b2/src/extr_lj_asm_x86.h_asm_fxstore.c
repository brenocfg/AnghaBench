#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86Op ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_17__ {int ofs; } ;
struct TYPE_19__ {TYPE_1__ mrm; } ;
struct TYPE_18__ {scalar_t__ r; scalar_t__ o; int /*<<< orphan*/  t; int /*<<< orphan*/  op1; int /*<<< orphan*/  op2; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_REX ; 
 int /*<<< orphan*/  IR (int /*<<< orphan*/ ) ; 
#define  IRT_FLOAT 134 
#define  IRT_I16 133 
#define  IRT_I8 132 
#define  IRT_LIGHTUD 131 
#define  IRT_NUM 130 
#define  IRT_U16 129 
#define  IRT_U8 128 
 scalar_t__ IR_FSTORE ; 
 scalar_t__ IR_HIOP ; 
 scalar_t__ LJ_32 ; 
 scalar_t__ LJ_64 ; 
 int /*<<< orphan*/  REX_64 ; 
 int /*<<< orphan*/  REX_64IR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_MRM ; 
 int /*<<< orphan*/  RID_NONE ; 
 scalar_t__ RID_SINK ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  RSET_GPR8 ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_MOVSDto ; 
 int /*<<< orphan*/  XO_MOVSSto ; 
 int /*<<< orphan*/  XO_MOVmi ; 
 int /*<<< orphan*/  XO_MOVmib ; 
 int /*<<< orphan*/  XO_MOVto ; 
 int /*<<< orphan*/  XO_MOVtob ; 
 int /*<<< orphan*/  XO_MOVtow ; 
 int /*<<< orphan*/  asm_fusefref (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_fusexref (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_isk32 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_i32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isi16 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isi8 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu32 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu8 (int /*<<< orphan*/ ) ; 
 int irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_scratch (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_fxstore(ASMState *as, IRIns *ir)
{
  RegSet allow = RSET_GPR;
  Reg src = RID_NONE, osrc = RID_NONE;
  int32_t k = 0;
  if (ir->r == RID_SINK)
    return;
  /* The IRT_I16/IRT_U16 stores should never be simplified for constant
  ** values since mov word [mem], imm16 has a length-changing prefix.
  */
  if (irt_isi16(ir->t) || irt_isu16(ir->t) || irt_isfp(ir->t) ||
      !asm_isk32(as, ir->op2, &k)) {
    RegSet allow8 = irt_isfp(ir->t) ? RSET_FPR :
		    (irt_isi8(ir->t) || irt_isu8(ir->t)) ? RSET_GPR8 : RSET_GPR;
    src = osrc = ra_alloc1(as, ir->op2, allow8);
    if (!LJ_64 && !rset_test(allow8, src)) {  /* Already in wrong register. */
      rset_clear(allow, osrc);
      src = ra_scratch(as, allow8);
    }
    rset_clear(allow, src);
  }
  if (ir->o == IR_FSTORE) {
    asm_fusefref(as, IR(ir->op1), allow);
  } else {
    asm_fusexref(as, ir->op1, allow);
    if (LJ_32 && ir->o == IR_HIOP) as->mrm.ofs += 4;
  }
  if (ra_hasreg(src)) {
    x86Op xo;
    switch (irt_type(ir->t)) {
    case IRT_I8: case IRT_U8: xo = XO_MOVtob; src |= FORCE_REX; break;
    case IRT_I16: case IRT_U16: xo = XO_MOVtow; break;
    case IRT_NUM: xo = XO_MOVSDto; break;
    case IRT_FLOAT: xo = XO_MOVSSto; break;
#if LJ_64
    case IRT_LIGHTUD: lua_assert(0);  /* NYI: mask 64 bit lightuserdata. */
#endif
    default:
      if (LJ_64 && irt_is64(ir->t))
	src |= REX_64;
      else
	lua_assert(irt_isint(ir->t) || irt_isu32(ir->t) || irt_isaddr(ir->t));
      xo = XO_MOVto;
      break;
    }
    emit_mrm(as, xo, src, RID_MRM);
    if (!LJ_64 && src != osrc) {
      ra_noweak(as, osrc);
      emit_rr(as, XO_MOV, src, osrc);
    }
  } else {
    if (irt_isi8(ir->t) || irt_isu8(ir->t)) {
      emit_i8(as, k);
      emit_mrm(as, XO_MOVmib, 0, RID_MRM);
    } else {
      lua_assert(irt_is64(ir->t) || irt_isint(ir->t) || irt_isu32(ir->t) ||
		 irt_isaddr(ir->t));
      emit_i32(as, k);
      emit_mrm(as, XO_MOVmi, REX_64IR(ir, 0), RID_MRM);
    }
  }
}