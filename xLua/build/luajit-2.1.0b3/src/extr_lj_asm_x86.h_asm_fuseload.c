#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int int32_t ;
struct TYPE_22__ {int ofs; void* idx; void* base; } ;
struct TYPE_25__ {int freeset; int modset; TYPE_1__ mrm; int /*<<< orphan*/  J; } ;
struct TYPE_24__ {scalar_t__ o; int op2; scalar_t__ op1; int /*<<< orphan*/  s; int /*<<< orphan*/  t; int /*<<< orphan*/  r; } ;
struct TYPE_23__ {int /*<<< orphan*/  jit_base; } ;
typedef  int RegSet ;
typedef  int /*<<< orphan*/  Reg ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (scalar_t__) ; 
 scalar_t__ IRDELTA_L2S ; 
 int IRSLOAD_CONVERT ; 
 int IRSLOAD_FRAME ; 
 int IRSLOAD_PARENT ; 
 int /*<<< orphan*/  IRT_I8 ; 
 int /*<<< orphan*/  IRT_U16 ; 
 scalar_t__ IR_ALOAD ; 
 scalar_t__ IR_FLOAD ; 
 scalar_t__ IR_FSTORE ; 
 scalar_t__ IR_HLOAD ; 
 scalar_t__ IR_KINT64 ; 
 scalar_t__ IR_KNUM ; 
 scalar_t__ IR_RETF ; 
 scalar_t__ IR_SLOAD ; 
 scalar_t__ IR_ULOAD ; 
 scalar_t__ IR_VLOAD ; 
 scalar_t__ IR_XLOAD ; 
 scalar_t__ IR_XSTORE ; 
 TYPE_20__* J2G (int /*<<< orphan*/ ) ; 
 int LJ_FR2 ; 
 scalar_t__ LJ_GC64 ; 
 scalar_t__ REF_BASE ; 
 scalar_t__ REF_NIL ; 
 void* RID_DISPATCH ; 
 void* RID_ESP ; 
 int /*<<< orphan*/  RID_MRM ; 
 void* RID_NONE ; 
 int RSET_EMPTY ; 
 int RSET_FPR ; 
 int RSET_GPR ; 
 int /*<<< orphan*/  asm_fuseahuref (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  asm_fusefref (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  asm_fuseloadk64 (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  asm_fusexref (TYPE_3__*,scalar_t__,int) ; 
 scalar_t__ dispofs (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_canremat (scalar_t__) ; 
 scalar_t__ irt_isaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_typerange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iscrossref (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ mayfuse (TYPE_3__*,scalar_t__) ; 
 scalar_t__ noconflict (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int ptr2addr (int /*<<< orphan*/ *) ; 
 scalar_t__ ra_alloc1 (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ra_allocref (TYPE_3__*,scalar_t__,int) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasspill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ra_spill (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static Reg asm_fuseload(ASMState *as, IRRef ref, RegSet allow)
{
  IRIns *ir = IR(ref);
  if (ra_hasreg(ir->r)) {
    if (allow != RSET_EMPTY) {  /* Fast path. */
      ra_noweak(as, ir->r);
      return ir->r;
    }
  fusespill:
    /* Force a spill if only memory operands are allowed (asm_x87load). */
    as->mrm.base = RID_ESP;
    as->mrm.ofs = ra_spill(as, ir);
    as->mrm.idx = RID_NONE;
    return RID_MRM;
  }
  if (ir->o == IR_KNUM) {
    RegSet avail = as->freeset & ~as->modset & RSET_FPR;
    lua_assert(allow != RSET_EMPTY);
    if (!(avail & (avail-1)))  /* Fuse if less than two regs available. */
      return asm_fuseloadk64(as, ir);
  } else if (ref == REF_BASE || ir->o == IR_KINT64) {
    RegSet avail = as->freeset & ~as->modset & RSET_GPR;
    lua_assert(allow != RSET_EMPTY);
    if (!(avail & (avail-1))) {  /* Fuse if less than two regs available. */
      if (ref == REF_BASE) {
#if LJ_GC64
	as->mrm.ofs = (int32_t)dispofs(as, &J2G(as->J)->jit_base);
	as->mrm.base = RID_DISPATCH;
#else
	as->mrm.ofs = ptr2addr(&J2G(as->J)->jit_base);
	as->mrm.base = RID_NONE;
#endif
	as->mrm.idx = RID_NONE;
	return RID_MRM;
      } else {
	return asm_fuseloadk64(as, ir);
      }
    }
  } else if (mayfuse(as, ref)) {
    RegSet xallow = (allow & RSET_GPR) ? allow : RSET_GPR;
    if (ir->o == IR_SLOAD) {
      if (!(ir->op2 & (IRSLOAD_PARENT|IRSLOAD_CONVERT)) &&
	  noconflict(as, ref, IR_RETF, 0) &&
	  !(LJ_GC64 && irt_isaddr(ir->t))) {
	as->mrm.base = (uint8_t)ra_alloc1(as, REF_BASE, xallow);
	as->mrm.ofs = 8*((int32_t)ir->op1-1-LJ_FR2) +
		      (!LJ_FR2 && (ir->op2 & IRSLOAD_FRAME) ? 4 : 0);
	as->mrm.idx = RID_NONE;
	return RID_MRM;
      }
    } else if (ir->o == IR_FLOAD) {
      /* Generic fusion is only ok for 32 bit operand (but see asm_comp). */
      if ((irt_isint(ir->t) || irt_isu32(ir->t) || irt_isaddr(ir->t)) &&
	  noconflict(as, ref, IR_FSTORE, 0)) {
	asm_fusefref(as, ir, xallow);
	return RID_MRM;
      }
    } else if (ir->o == IR_ALOAD || ir->o == IR_HLOAD || ir->o == IR_ULOAD) {
      if (noconflict(as, ref, ir->o + IRDELTA_L2S, 0) &&
	  !(LJ_GC64 && irt_isaddr(ir->t))) {
	asm_fuseahuref(as, ir->op1, xallow);
	return RID_MRM;
      }
    } else if (ir->o == IR_XLOAD) {
      /* Generic fusion is not ok for 8/16 bit operands (but see asm_comp).
      ** Fusing unaligned memory operands is ok on x86 (except for SIMD types).
      */
      if ((!irt_typerange(ir->t, IRT_I8, IRT_U16)) &&
	  noconflict(as, ref, IR_XSTORE, 0)) {
	asm_fusexref(as, ir->op1, xallow);
	return RID_MRM;
      }
    } else if (ir->o == IR_VLOAD && !(LJ_GC64 && irt_isaddr(ir->t))) {
      asm_fuseahuref(as, ir->op1, xallow);
      return RID_MRM;
    }
  }
  if (ir->o == IR_FLOAD && ir->op1 == REF_NIL) {
    asm_fusefref(as, ir, RSET_EMPTY);
    return RID_MRM;
  }
  if (!(as->freeset & allow) && !emit_canremat(ref) &&
      (allow == RSET_EMPTY || ra_hasspill(ir->s) || iscrossref(as, ref)))
    goto fusespill;
  return ra_allocref(as, ref, allow);
}