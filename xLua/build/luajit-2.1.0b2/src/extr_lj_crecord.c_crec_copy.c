#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_9__ {int /*<<< orphan*/  i; } ;
struct TYPE_8__ {int info; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  scalar_t__ MSize ;
typedef  size_t IRType ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;
typedef  int /*<<< orphan*/  CRecMemList ;

/* Variables and functions */
 int CREC_COPY_MAXLEN ; 
 int CREC_COPY_MAXUNROLL ; 
 int CTF_UNION ; 
 int CTSIZE_PTR ; 
 TYPE_7__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRCALL_memcpy ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t IRT_CDATA ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IR_XBAR ; 
 int /*<<< orphan*/  J2G (int /*<<< orphan*/ *) ; 
 scalar_t__ LJ_TARGET_UNALIGNED ; 
 int /*<<< orphan*/  crec_copy_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crec_copy_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ crec_copy_unroll (int /*<<< orphan*/ *,int,int,size_t) ; 
 size_t crec_ct2irt (int /*<<< orphan*/ *,TYPE_1__*) ; 
 unsigned int ctype_align (int) ; 
 int /*<<< orphan*/ * ctype_ctsG (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isarray (int) ; 
 scalar_t__ ctype_isstruct (int) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* lj_ir_type_size ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ tref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crec_copy(jit_State *J, TRef trdst, TRef trsrc, TRef trlen,
		      CType *ct)
{
  if (tref_isk(trlen)) {  /* Length must be constant. */
    CRecMemList ml[CREC_COPY_MAXUNROLL];
    MSize mlp = 0;
    CTSize step = 1, len = (CTSize)IR(tref_ref(trlen))->i;
    IRType tp = IRT_CDATA;
    int needxbar = 0;
    if (len == 0) return;  /* Shortcut. */
    if (len > CREC_COPY_MAXLEN) goto fallback;
    if (ct) {
      CTState *cts = ctype_ctsG(J2G(J));
      lua_assert(ctype_isarray(ct->info) || ctype_isstruct(ct->info));
      if (ctype_isarray(ct->info)) {
	CType *cct = ctype_rawchild(cts, ct);
	tp = crec_ct2irt(cts, cct);
	if (tp == IRT_CDATA) goto rawcopy;
	step = lj_ir_type_size[tp];
	lua_assert((len & (step-1)) == 0);
      } else if ((ct->info & CTF_UNION)) {
	step = (1u << ctype_align(ct->info));
	goto rawcopy;
      } else {
	mlp = crec_copy_struct(ml, cts, ct);
	goto emitcopy;
      }
    } else {
    rawcopy:
      needxbar = 1;
      if (LJ_TARGET_UNALIGNED || step >= CTSIZE_PTR)
	step = CTSIZE_PTR;
    }
    mlp = crec_copy_unroll(ml, len, step, tp);
  emitcopy:
    if (mlp) {
      crec_copy_emit(J, ml, mlp, trdst, trsrc);
      if (needxbar)
	emitir(IRT(IR_XBAR, IRT_NIL), 0, 0);
      return;
    }
  }
fallback:
  /* Call memcpy. Always needs a barrier to disable alias analysis. */
  lj_ir_call(J, IRCALL_memcpy, trdst, trsrc, trlen);
  emitir(IRT(IR_XBAR, IRT_NIL), 0, 0);
}