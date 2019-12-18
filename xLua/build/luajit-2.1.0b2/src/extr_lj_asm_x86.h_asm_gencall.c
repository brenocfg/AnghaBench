#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_27__ {scalar_t__ hi; scalar_t__ lo; } ;
struct TYPE_31__ {TYPE_1__ u32; } ;
struct TYPE_30__ {int* mcp; int /*<<< orphan*/  freeset; } ;
struct TYPE_29__ {int flags; scalar_t__ func; } ;
struct TYPE_28__ {scalar_t__ o; int i; int /*<<< orphan*/  t; int /*<<< orphan*/  r; } ;
struct TYPE_26__ {int /*<<< orphan*/  u64; } ;
typedef  int Reg ;
typedef  int MCode ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ CCallInfo ;
typedef  TYPE_4__ ASMState ;

/* Variables and functions */
 scalar_t__ ASMREF_TMP1 ; 
 int CCI_CC_CDECL ; 
 int CCI_CC_FASTCALL ; 
 int CCI_CC_MASK ; 
 int CCI_CC_THISCALL ; 
 int CCI_VARARG ; 
 int CCI_XNARGS (TYPE_3__ const*) ; 
 TYPE_2__* IR (scalar_t__) ; 
 scalar_t__ IR_KINT64 ; 
 scalar_t__ LJ_32 ; 
 void* REGARG_FIRSTFPR ; 
 int REGARG_GPRS ; 
 int REGARG_LASTFPR ; 
 int REX_64 ; 
 int /*<<< orphan*/  RID2RSET (int) ; 
 int RID_EAX ; 
 int /*<<< orphan*/  RID_ESP ; 
 int RID_MAX_GPR ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int STACKARG_OFS ; 
 int XI_MOVrib ; 
 int /*<<< orphan*/  XO_MOVDto ; 
 int /*<<< orphan*/  XO_MOVSDto ; 
 int /*<<< orphan*/  XO_MOVSSto ; 
 int /*<<< orphan*/  checkmclim (TYPE_4__*) ; 
 int /*<<< orphan*/  emit_call (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  emit_loadi (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  emit_loadu64 (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movmroi (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_movrr (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movtomro (TYPE_4__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_rr (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_10__* ir_kint64 (TYPE_2__*) ; 
 TYPE_8__* ir_knum (TYPE_2__*) ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 scalar_t__ irt_isfloat (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int ra_alloc1 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_allocref (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int rset_test (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asm_gencall(ASMState *as, const CCallInfo *ci, IRRef *args)
{
  uint32_t n, nargs = CCI_XNARGS(ci);
  int32_t ofs = STACKARG_OFS;
#if LJ_64
  uint32_t gprs = REGARG_GPRS;
  Reg fpr = REGARG_FIRSTFPR;
#if !LJ_ABI_WIN
  MCode *patchnfpr = NULL;
#endif
#else
  uint32_t gprs = 0;
  if ((ci->flags & CCI_CC_MASK) != CCI_CC_CDECL) {
    if ((ci->flags & CCI_CC_MASK) == CCI_CC_THISCALL)
      gprs = (REGARG_GPRS & 31);
    else if ((ci->flags & CCI_CC_MASK) == CCI_CC_FASTCALL)
      gprs = REGARG_GPRS;
  }
#endif
  if ((void *)ci->func)
    emit_call(as, ci->func);
#if LJ_64
  if ((ci->flags & CCI_VARARG)) {  /* Special handling for vararg calls. */
#if LJ_ABI_WIN
    for (n = 0; n < 4 && n < nargs; n++) {
      IRIns *ir = IR(args[n]);
      if (irt_isfp(ir->t))  /* Duplicate FPRs in GPRs. */
	emit_rr(as, XO_MOVDto, (irt_isnum(ir->t) ? REX_64 : 0) | (fpr+n),
		((gprs >> (n*5)) & 31));  /* Either MOVD or MOVQ. */
    }
#else
    patchnfpr = --as->mcp;  /* Indicate number of used FPRs in register al. */
    *--as->mcp = XI_MOVrib | RID_EAX;
#endif
  }
#endif
  for (n = 0; n < nargs; n++) {  /* Setup args. */
    IRRef ref = args[n];
    IRIns *ir = IR(ref);
    Reg r;
#if LJ_64 && LJ_ABI_WIN
    /* Windows/x64 argument registers are strictly positional. */
    r = irt_isfp(ir->t) ? (fpr <= REGARG_LASTFPR ? fpr : 0) : (gprs & 31);
    fpr++; gprs >>= 5;
#elif LJ_64
    /* POSIX/x64 argument registers are used in order of appearance. */
    if (irt_isfp(ir->t)) {
      r = fpr <= REGARG_LASTFPR ? fpr++ : 0;
    } else {
      r = gprs & 31; gprs >>= 5;
    }
#else
    if (ref && irt_isfp(ir->t)) {
      r = 0;
    } else {
      r = gprs & 31; gprs >>= 5;
      if (!ref) continue;
    }
#endif
    if (r) {  /* Argument is in a register. */
      if (r < RID_MAX_GPR && ref < ASMREF_TMP1) {
#if LJ_64
	if (ir->o == IR_KINT64)
	  emit_loadu64(as, r, ir_kint64(ir)->u64);
	else
#endif
	  emit_loadi(as, r, ir->i);
      } else {
	lua_assert(rset_test(as->freeset, r));  /* Must have been evicted. */
	if (ra_hasreg(ir->r)) {
	  ra_noweak(as, ir->r);
	  emit_movrr(as, ir, r, ir->r);
	} else {
	  ra_allocref(as, ref, RID2RSET(r));
	}
      }
    } else if (irt_isfp(ir->t)) {  /* FP argument is on stack. */
      lua_assert(!(irt_isfloat(ir->t) && irref_isk(ref)));  /* No float k. */
      if (LJ_32 && (ofs & 4) && irref_isk(ref)) {
	/* Split stores for unaligned FP consts. */
	emit_movmroi(as, RID_ESP, ofs, (int32_t)ir_knum(ir)->u32.lo);
	emit_movmroi(as, RID_ESP, ofs+4, (int32_t)ir_knum(ir)->u32.hi);
      } else {
	r = ra_alloc1(as, ref, RSET_FPR);
	emit_rmro(as, irt_isnum(ir->t) ? XO_MOVSDto : XO_MOVSSto,
		  r, RID_ESP, ofs);
      }
      ofs += (LJ_32 && irt_isfloat(ir->t)) ? 4 : 8;
    } else {  /* Non-FP argument is on stack. */
      if (LJ_32 && ref < ASMREF_TMP1) {
	emit_movmroi(as, RID_ESP, ofs, ir->i);
      } else {
	r = ra_alloc1(as, ref, RSET_GPR);
	emit_movtomro(as, REX_64 + r, RID_ESP, ofs);
      }
      ofs += sizeof(intptr_t);
    }
    checkmclim(as);
  }
#if LJ_64 && !LJ_ABI_WIN
  if (patchnfpr) *patchnfpr = fpr - REGARG_FIRSTFPR;
#endif
}