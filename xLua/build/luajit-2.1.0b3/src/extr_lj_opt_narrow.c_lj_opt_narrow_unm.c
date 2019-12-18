#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRCONV_NUM_INT ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IR_CONV ; 
 int /*<<< orphan*/  IR_NEG ; 
 int /*<<< orphan*/  IR_SUBOV ; 
 int /*<<< orphan*/  LJ_KSIMD_NEG ; 
 int /*<<< orphan*/  conv_str_tonum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_ksimd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ numberVint (int /*<<< orphan*/ *) ; 
 scalar_t__ tref_isinteger (int /*<<< orphan*/ ) ; 

TRef lj_opt_narrow_unm(jit_State *J, TRef rc, TValue *vc)
{
  rc = conv_str_tonum(J, rc, vc);
  if (tref_isinteger(rc)) {
    if ((uint32_t)numberVint(vc) != 0x80000000u)
      return emitir(IRTGI(IR_SUBOV), lj_ir_kint(J, 0), rc);
    rc = emitir(IRTN(IR_CONV), rc, IRCONV_NUM_INT);
  }
  return emitir(IRTN(IR_NEG), rc, lj_ir_ksimd(J, LJ_KSIMD_NEG));
}