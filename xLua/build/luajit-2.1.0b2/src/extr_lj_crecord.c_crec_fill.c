#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_6__ {int /*<<< orphan*/  i; } ;
struct TYPE_5__ {scalar_t__ tp; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  MSize ;
typedef  int CTSize ;
typedef  TYPE_1__ CRecMemList ;

/* Variables and functions */
 int CREC_FILL_MAXUNROLL ; 
 int CTSIZE_PTR ; 
 TYPE_4__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRCALL_memset ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ IRT_NIL ; 
 scalar_t__ IRT_U16 ; 
 scalar_t__ IRT_U32 ; 
 scalar_t__ IRT_U64 ; 
 scalar_t__ IRT_U8 ; 
 int /*<<< orphan*/  IR_MUL ; 
 int /*<<< orphan*/  IR_XBAR ; 
 scalar_t__ LJ_TARGET_UNALIGNED ; 
 int /*<<< orphan*/  U64x (int,int) ; 
 int /*<<< orphan*/  crec_fill_emit (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crec_fill_unroll (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  emitconv (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_ir_kint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crec_fill(jit_State *J, TRef trdst, TRef trlen, TRef trfill,
		      CTSize step)
{
  if (tref_isk(trlen)) {  /* Length must be constant. */
    CRecMemList ml[CREC_FILL_MAXUNROLL];
    MSize mlp;
    CTSize len = (CTSize)IR(tref_ref(trlen))->i;
    if (len == 0) return;  /* Shortcut. */
    if (LJ_TARGET_UNALIGNED || step >= CTSIZE_PTR)
      step = CTSIZE_PTR;
    if (step * CREC_FILL_MAXUNROLL < len) goto fallback;
    mlp = crec_fill_unroll(ml, len, step);
    if (!mlp) goto fallback;
    if (tref_isk(trfill) || ml[0].tp != IRT_U8)
      trfill = emitconv(trfill, IRT_INT, IRT_U8, 0);
    if (ml[0].tp != IRT_U8) {  /* Scatter U8 to U16/U32/U64. */
      if (CTSIZE_PTR == 8 && ml[0].tp == IRT_U64) {
	if (tref_isk(trfill))  /* Pointless on x64 with zero-extended regs. */
	  trfill = emitconv(trfill, IRT_U64, IRT_U32, 0);
	trfill = emitir(IRT(IR_MUL, IRT_U64), trfill,
			lj_ir_kint64(J, U64x(01010101,01010101)));
      } else {
	trfill = emitir(IRTI(IR_MUL), trfill,
		   lj_ir_kint(J, ml[0].tp == IRT_U16 ? 0x0101 : 0x01010101));
      }
    }
    crec_fill_emit(J, ml, mlp, trdst, trfill);
  } else {
fallback:
    /* Call memset. Always needs a barrier to disable alias analysis. */
    lj_ir_call(J, IRCALL_memset, trdst, trfill, trlen);  /* Note: arg order! */
  }
  emitir(IRT(IR_XBAR, IRT_NIL), 0, 0);
}