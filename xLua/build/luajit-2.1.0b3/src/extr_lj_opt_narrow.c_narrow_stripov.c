#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_6__ {int val; } ;
struct TYPE_5__ {int o; int op1; int op2; int /*<<< orphan*/  t; } ;
typedef  int TRef ;
typedef  int IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ BPropEntry ;

/* Variables and functions */
 TYPE_1__* IR (int) ; 
 int IRCONV_DSH ; 
 int IRCONV_DSTMASK ; 
 int IRCONV_SEXT ; 
 int /*<<< orphan*/  IRT (int,int) ; 
 int IRT_INTP ; 
 int IR_ADD ; 
 int IR_ADDOV ; 
 int IR_CONV ; 
 scalar_t__ LJ_64 ; 
 int TREF (int,int /*<<< orphan*/ ) ; 
 int emitir (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  irt_is64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_t (int /*<<< orphan*/ ) ; 
 TYPE_2__* narrow_bpc_get (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  narrow_bpc_set (int /*<<< orphan*/ *,int,int,int) ; 
 int tref_ref (int) ; 

__attribute__((used)) static TRef narrow_stripov(jit_State *J, TRef tr, int lastop, IRRef mode)
{
  IRRef ref = tref_ref(tr);
  IRIns *ir = IR(ref);
  int op = ir->o;
  if (op >= IR_ADDOV && op <= lastop) {
    BPropEntry *bp = narrow_bpc_get(J, ref, mode);
    if (bp) {
      return TREF(bp->val, irt_t(IR(bp->val)->t));
    } else {
      IRRef op1 = ir->op1, op2 = ir->op2;  /* The IR may be reallocated. */
      op1 = narrow_stripov(J, op1, lastop, mode);
      op2 = narrow_stripov(J, op2, lastop, mode);
      tr = emitir(IRT(op - IR_ADDOV + IR_ADD,
		      ((mode & IRCONV_DSTMASK) >> IRCONV_DSH)), op1, op2);
      narrow_bpc_set(J, ref, tref_ref(tr), mode);
    }
  } else if (LJ_64 && (mode & IRCONV_SEXT) && !irt_is64(ir->t)) {
    tr = emitir(IRT(IR_CONV, IRT_INTP), tr, mode);
  }
  return tr;
}