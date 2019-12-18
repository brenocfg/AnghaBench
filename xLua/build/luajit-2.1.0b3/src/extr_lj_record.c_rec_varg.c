#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ptrdiff_t ;
struct TYPE_13__ {int maxslot; int* base; scalar_t__ framedepth; int bcskip; int /*<<< orphan*/  errinfo; TYPE_2__* L; TYPE_1__* pt; } ;
typedef  TYPE_3__ jit_State ;
typedef  int int32_t ;
struct TYPE_12__ {int /*<<< orphan*/ * base; } ;
struct TYPE_11__ {int numparams; } ;
typedef  int TRef ;
typedef  int /*<<< orphan*/  IRType ;
typedef  int BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  BC_VARG ; 
 int FRAME_VARG ; 
 int IRCONV_INDEX ; 
 int IRCONV_INT_NUM ; 
 int IRSLOAD_FRAME ; 
 int IRSLOAD_READONLY ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_IGC ; 
 int /*<<< orphan*/  IRT_PGC ; 
 int /*<<< orphan*/  IR_ADD ; 
 int /*<<< orphan*/  IR_AREF ; 
 int /*<<< orphan*/  IR_BSHL ; 
 int /*<<< orphan*/  IR_BSHR ; 
 int /*<<< orphan*/  IR_CONV ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  IR_GE ; 
 int /*<<< orphan*/  IR_LE ; 
 int /*<<< orphan*/  IR_LT ; 
 int /*<<< orphan*/  IR_SLOAD ; 
 int /*<<< orphan*/  IR_SUB ; 
 int /*<<< orphan*/  IR_VLOAD ; 
 int LJ_FR2 ; 
 int /*<<< orphan*/  LJ_TRERR_NYIBC ; 
 int REF_BASE ; 
 void* TREF_NIL ; 
 int TREF_PRI (int /*<<< orphan*/ ) ; 
 int emitir (int /*<<< orphan*/ ,int,int) ; 
 int frame_delta (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_ftsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_isvarg (int /*<<< orphan*/ *) ; 
 void* getslot (TYPE_3__*,int) ; 
 scalar_t__ irtype_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itype2irt (int /*<<< orphan*/ *) ; 
 int lj_ffrecord_select_mode (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int lj_ir_kint (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lj_trace_err_info (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rec_idx_abc (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ select_detect (TYPE_3__*) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_isinteger (int) ; 
 scalar_t__ tref_isk (int) ; 

__attribute__((used)) static void rec_varg(jit_State *J, BCReg dst, ptrdiff_t nresults)
{
  int32_t numparams = J->pt->numparams;
  ptrdiff_t nvararg = frame_delta(J->L->base-1) - numparams - 1 - LJ_FR2;
  lua_assert(frame_isvarg(J->L->base-1));
  if (LJ_FR2 && dst > J->maxslot)
    J->base[dst-1] = 0;  /* Prevent resurrection of unrelated slot. */
  if (J->framedepth > 0) {  /* Simple case: varargs defined on-trace. */
    ptrdiff_t i;
    if (nvararg < 0) nvararg = 0;
    if (nresults == -1) {
      nresults = nvararg;
      J->maxslot = dst + (BCReg)nvararg;
    } else if (dst + nresults > J->maxslot) {
      J->maxslot = dst + (BCReg)nresults;
    }
    for (i = 0; i < nresults; i++)
      J->base[dst+i] = i < nvararg ? getslot(J, i - nvararg - 1 - LJ_FR2) : TREF_NIL;
  } else {  /* Unknown number of varargs passed to trace. */
    TRef fr = emitir(IRTI(IR_SLOAD), LJ_FR2, IRSLOAD_READONLY|IRSLOAD_FRAME);
    int32_t frofs = 8*(1+LJ_FR2+numparams)+FRAME_VARG;
    if (nresults >= 0) {  /* Known fixed number of results. */
      ptrdiff_t i;
      if (nvararg > 0) {
	ptrdiff_t nload = nvararg >= nresults ? nresults : nvararg;
	TRef vbase;
	if (nvararg >= nresults)
	  emitir(IRTGI(IR_GE), fr, lj_ir_kint(J, frofs+8*(int32_t)nresults));
	else
	  emitir(IRTGI(IR_EQ), fr,
		 lj_ir_kint(J, (int32_t)frame_ftsz(J->L->base-1)));
	vbase = emitir(IRT(IR_SUB, IRT_IGC), REF_BASE, fr);
	vbase = emitir(IRT(IR_ADD, IRT_PGC), vbase, lj_ir_kint(J, frofs-8));
	for (i = 0; i < nload; i++) {
	  IRType t = itype2irt(&J->L->base[i-1-LJ_FR2-nvararg]);
	  TRef aref = emitir(IRT(IR_AREF, IRT_PGC),
			     vbase, lj_ir_kint(J, (int32_t)i));
	  TRef tr = emitir(IRTG(IR_VLOAD, t), aref, 0);
	  if (irtype_ispri(t)) tr = TREF_PRI(t);  /* Canonicalize primitives. */
	  J->base[dst+i] = tr;
	}
      } else {
	emitir(IRTGI(IR_LE), fr, lj_ir_kint(J, frofs));
	nvararg = 0;
      }
      for (i = nvararg; i < nresults; i++)
	J->base[dst+i] = TREF_NIL;
      if (dst + (BCReg)nresults > J->maxslot)
	J->maxslot = dst + (BCReg)nresults;
    } else if (select_detect(J)) {  /* y = select(x, ...) */
      TRef tridx = J->base[dst-1];
      TRef tr = TREF_NIL;
      ptrdiff_t idx = lj_ffrecord_select_mode(J, tridx, &J->L->base[dst-1]);
      if (idx < 0) goto nyivarg;
      if (idx != 0 && !tref_isinteger(tridx))
	tridx = emitir(IRTGI(IR_CONV), tridx, IRCONV_INT_NUM|IRCONV_INDEX);
      if (idx != 0 && tref_isk(tridx)) {
	emitir(IRTGI(idx <= nvararg ? IR_GE : IR_LT),
	       fr, lj_ir_kint(J, frofs+8*(int32_t)idx));
	frofs -= 8;  /* Bias for 1-based index. */
      } else if (idx <= nvararg) {  /* Compute size. */
	TRef tmp = emitir(IRTI(IR_ADD), fr, lj_ir_kint(J, -frofs));
	if (numparams)
	  emitir(IRTGI(IR_GE), tmp, lj_ir_kint(J, 0));
	tr = emitir(IRTI(IR_BSHR), tmp, lj_ir_kint(J, 3));
	if (idx != 0) {
	  tridx = emitir(IRTI(IR_ADD), tridx, lj_ir_kint(J, -1));
	  rec_idx_abc(J, tr, tridx, (uint32_t)nvararg);
	}
      } else {
	TRef tmp = lj_ir_kint(J, frofs);
	if (idx != 0) {
	  TRef tmp2 = emitir(IRTI(IR_BSHL), tridx, lj_ir_kint(J, 3));
	  tmp = emitir(IRTI(IR_ADD), tmp2, tmp);
	} else {
	  tr = lj_ir_kint(J, 0);
	}
	emitir(IRTGI(IR_LT), fr, tmp);
      }
      if (idx != 0 && idx <= nvararg) {
	IRType t;
	TRef aref, vbase = emitir(IRT(IR_SUB, IRT_IGC), REF_BASE, fr);
	vbase = emitir(IRT(IR_ADD, IRT_PGC), vbase,
		       lj_ir_kint(J, frofs-(8<<LJ_FR2)));
	t = itype2irt(&J->L->base[idx-2-LJ_FR2-nvararg]);
	aref = emitir(IRT(IR_AREF, IRT_PGC), vbase, tridx);
	tr = emitir(IRTG(IR_VLOAD, t), aref, 0);
	if (irtype_ispri(t)) tr = TREF_PRI(t);  /* Canonicalize primitives. */
      }
      J->base[dst-2-LJ_FR2] = tr;
      J->maxslot = dst-1-LJ_FR2;
      J->bcskip = 2;  /* Skip CALLM + select. */
    } else {
    nyivarg:
      setintV(&J->errinfo, BC_VARG);
      lj_trace_err_info(J, LJ_TRERR_NYIBC);
    }
  }
}