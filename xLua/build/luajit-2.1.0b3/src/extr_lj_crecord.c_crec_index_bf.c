#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int needsnap; int /*<<< orphan*/ * base; int /*<<< orphan*/  postproc; } ;
typedef  TYPE_1__ jit_State ;
typedef  int int32_t ;
struct TYPE_10__ {scalar_t__ data; scalar_t__ nres; int /*<<< orphan*/ * argv; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  TYPE_2__ RecordFFData ;
typedef  scalar_t__ IRType ;
typedef  int /*<<< orphan*/  CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_BOOL ; 
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_BOOL ; 
 int /*<<< orphan*/  CTID_INT32 ; 
 int /*<<< orphan*/  CTID_UINT32 ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 scalar_t__ IRT_I8 ; 
 scalar_t__ IRT_U32 ; 
 int /*<<< orphan*/  IR_BAND ; 
 int /*<<< orphan*/  IR_BOR ; 
 int /*<<< orphan*/  IR_BSAR ; 
 int /*<<< orphan*/  IR_BSHL ; 
 int /*<<< orphan*/  IR_BSHR ; 
 int /*<<< orphan*/  IR_NE ; 
 int /*<<< orphan*/  IR_XLOAD ; 
 int /*<<< orphan*/  IR_XSTORE ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 int /*<<< orphan*/  LJ_POST_FIXGUARD ; 
 int /*<<< orphan*/  TREF_TRUE ; 
 int /*<<< orphan*/  crec_ct_tv (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ctype_bitbsz (int) ; 
 int /*<<< orphan*/  ctype_bitcsz (int) ; 
 int ctype_bitpos (int) ; 
 int /*<<< orphan*/ * ctype_ctsG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lj_fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_ir_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void crec_index_bf(jit_State *J, RecordFFData *rd, TRef ptr, CTInfo info)
{
  IRType t = IRT_I8 + 2*lj_fls(ctype_bitcsz(info)) + ((info&CTF_UNSIGNED)?1:0);
  TRef tr = emitir(IRT(IR_XLOAD, t), ptr, 0);
  CTSize pos = ctype_bitpos(info), bsz = ctype_bitbsz(info), shift = 32 - bsz;
  lua_assert(t <= IRT_U32);  /* NYI: 64 bit bitfields. */
  if (rd->data == 0) {  /* __index metamethod. */
    if ((info & CTF_BOOL)) {
      tr = emitir(IRTI(IR_BAND), tr, lj_ir_kint(J, (int32_t)((1u << pos))));
      /* Assume not equal to zero. Fixup and emit pending guard later. */
      lj_ir_set(J, IRTGI(IR_NE), tr, lj_ir_kint(J, 0));
      J->postproc = LJ_POST_FIXGUARD;
      tr = TREF_TRUE;
    } else if (!(info & CTF_UNSIGNED)) {
      tr = emitir(IRTI(IR_BSHL), tr, lj_ir_kint(J, shift - pos));
      tr = emitir(IRTI(IR_BSAR), tr, lj_ir_kint(J, shift));
    } else {
      lua_assert(bsz < 32);  /* Full-size fields cannot end up here. */
      tr = emitir(IRTI(IR_BSHR), tr, lj_ir_kint(J, pos));
      tr = emitir(IRTI(IR_BAND), tr, lj_ir_kint(J, (int32_t)((1u << bsz)-1)));
      /* We can omit the U32 to NUM conversion, since bsz < 32. */
    }
    J->base[0] = tr;
  } else {  /* __newindex metamethod. */
    CTState *cts = ctype_ctsG(J2G(J));
    CType *ct = ctype_get(cts,
			  (info & CTF_BOOL) ? CTID_BOOL :
			  (info & CTF_UNSIGNED) ? CTID_UINT32 : CTID_INT32);
    int32_t mask = (int32_t)(((1u << bsz)-1) << pos);
    TRef sp = crec_ct_tv(J, ct, 0, J->base[2], &rd->argv[2]);
    sp = emitir(IRTI(IR_BSHL), sp, lj_ir_kint(J, pos));
    /* Use of the target type avoids forwarding conversions. */
    sp = emitir(IRT(IR_BAND, t), sp, lj_ir_kint(J, mask));
    tr = emitir(IRT(IR_BAND, t), tr, lj_ir_kint(J, (int32_t)~mask));
    tr = emitir(IRT(IR_BOR, t), tr, sp);
    emitir(IRT(IR_XSTORE, t), ptr, tr);
    rd->nres = 0;
    J->needsnap = 1;
  }
}