#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ hi; } ;
struct TYPE_5__ {double n; TYPE_1__ u32; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IR (int /*<<< orphan*/ ) ; 
 int IRCONV_CHECK ; 
 int IRCONV_INT_NUM ; 
 int IRFPM_EXP2 ; 
 int IRFPM_LOG2 ; 
 int IRFPM_SQRT ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IR_ADD ; 
 int /*<<< orphan*/  IR_CONV ; 
 int /*<<< orphan*/  IR_FPMATH ; 
 int /*<<< orphan*/  IR_MUL ; 
 int /*<<< orphan*/  IR_POW ; 
 int /*<<< orphan*/  IR_ULE ; 
 int conv_str_tonum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int emitir (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ir_knum (int /*<<< orphan*/ ) ; 
 int lj_ir_kint (int /*<<< orphan*/ *,int) ; 
 int lj_ir_tonum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 scalar_t__ numberVint (int /*<<< orphan*/ *) ; 
 scalar_t__ numisint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_isinteger (int) ; 
 scalar_t__ tref_isk (int) ; 
 int /*<<< orphan*/  tref_ref (int) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvispone (TYPE_2__*) ; 

TRef lj_opt_narrow_pow(jit_State *J, TRef rb, TRef rc, TValue *vb, TValue *vc)
{
  rb = conv_str_tonum(J, rb, vb);
  rb = lj_ir_tonum(J, rb);  /* Left arg is always treated as an FP number. */
  rc = conv_str_tonum(J, rc, vc);
  /* Narrowing must be unconditional to preserve (-x)^i semantics. */
  if (tvisint(vc) || numisint(numV(vc))) {
    int checkrange = 0;
    /* Split pow is faster for bigger exponents. But do this only for (+k)^i. */
    if (tref_isk(rb) && (int32_t)ir_knum(IR(tref_ref(rb)))->u32.hi >= 0) {
      int32_t k = numberVint(vc);
      if (!(k >= -65536 && k <= 65536)) goto split_pow;
      checkrange = 1;
    }
    if (!tref_isinteger(rc)) {
      /* Guarded conversion to integer! */
      rc = emitir(IRTGI(IR_CONV), rc, IRCONV_INT_NUM|IRCONV_CHECK);
    }
    if (checkrange && !tref_isk(rc)) {  /* Range guard: -65536 <= i <= 65536 */
      TRef tmp = emitir(IRTI(IR_ADD), rc, lj_ir_kint(J, 65536));
      emitir(IRTGI(IR_ULE), tmp, lj_ir_kint(J, 2*65536));
    }
    return emitir(IRTN(IR_POW), rb, rc);
  }
split_pow:
  /* FOLD covers most cases, but some are easier to do here. */
  if (tref_isk(rb) && tvispone(ir_knum(IR(tref_ref(rb)))))
    return rb;  /* 1 ^ x ==> 1 */
  rc = lj_ir_tonum(J, rc);
  if (tref_isk(rc) && ir_knum(IR(tref_ref(rc)))->n == 0.5)
    return emitir(IRTN(IR_FPMATH), rb, IRFPM_SQRT);  /* x ^ 0.5 ==> sqrt(x) */
  /* Split up b^c into exp2(c*log2(b)). Assembler may rejoin later. */
  rb = emitir(IRTN(IR_FPMATH), rb, IRFPM_LOG2);
  rc = emitir(IRTN(IR_MUL), rb, rc);
  return emitir(IRTN(IR_FPMATH), rc, IRFPM_EXP2);
}