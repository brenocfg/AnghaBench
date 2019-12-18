#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_12__ {scalar_t__* base; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
typedef  int int32_t ;
struct TYPE_13__ {int /*<<< orphan*/ * argv; } ;
typedef  scalar_t__ TRef ;
typedef  int SFormat ;
typedef  TYPE_2__ RecordFFData ;
typedef  scalar_t__ CTypeID ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 scalar_t__ CTID_INT32 ; 
 int /*<<< orphan*/  IRCALL_lj_strfmt_putfxint ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_INT ; 
 int /*<<< orphan*/  IRT_U64 ; 
 int /*<<< orphan*/  IR_BAND ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 int STRFMT_F_UPPER ; 
 int STRFMT_SH_PREC ; 
 int STRFMT_T_HEX ; 
 int STRFMT_UINT ; 
 scalar_t__ crec_bit64_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ crec_ct_tv (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ctype_ctsG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ emitconv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emitir (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_carith_check64 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ lj_ir_call (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_ir_kint64 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_needsplit (TYPE_1__*) ; 
 scalar_t__ lj_opt_narrow_tobit (TYPE_1__*,scalar_t__) ; 

TRef recff_bit64_tohex(jit_State *J, RecordFFData *rd, TRef hdr)
{
  CTState *cts = ctype_ctsG(J2G(J));
  CTypeID id = crec_bit64_type(cts, &rd->argv[0]);
  TRef tr, trsf = J->base[1];
  SFormat sf = (STRFMT_UINT|STRFMT_T_HEX);
  int32_t n;
  if (trsf) {
    CTypeID id2 = 0;
    n = (int32_t)lj_carith_check64(J->L, 2, &id2);
    if (id2)
      trsf = crec_ct_tv(J, ctype_get(cts, CTID_INT32), 0, trsf, &rd->argv[1]);
    else
      trsf = lj_opt_narrow_tobit(J, trsf);
    emitir(IRTGI(IR_EQ), trsf, lj_ir_kint(J, n));  /* Specialize to n. */
  } else {
    n = id ? 16 : 8;
  }
  if (n < 0) { n = -n; sf |= STRFMT_F_UPPER; }
  sf |= ((SFormat)((n+1)&255) << STRFMT_SH_PREC);
  if (id) {
    tr = crec_ct_tv(J, ctype_get(cts, id), 0, J->base[0], &rd->argv[0]);
    if (n < 16)
      tr = emitir(IRT(IR_BAND, IRT_U64), tr,
		  lj_ir_kint64(J, ((uint64_t)1 << 4*n)-1));
  } else {
    tr = lj_opt_narrow_tobit(J, J->base[0]);
    if (n < 8)
      tr = emitir(IRTI(IR_BAND), tr, lj_ir_kint(J, (int32_t)((1u << 4*n)-1)));
    tr = emitconv(tr, IRT_U64, IRT_INT, 0);  /* No sign-extension. */
    lj_needsplit(J);
  }
  return lj_ir_call(J, IRCALL_lj_strfmt_putfxint, hdr, lj_ir_kint(J, sf), tr);
}