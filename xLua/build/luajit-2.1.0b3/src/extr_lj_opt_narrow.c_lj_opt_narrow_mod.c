#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRFPM_FLOOR ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IR_DIV ; 
 int /*<<< orphan*/  IR_FPMATH ; 
 int /*<<< orphan*/  IR_MOD ; 
 int /*<<< orphan*/  IR_MUL ; 
 int /*<<< orphan*/  IR_NE ; 
 int /*<<< orphan*/  IR_SUB ; 
 int JIT_F_OPT_NARROW ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  conv_str_tonum (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_tonum (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tviszero (int /*<<< orphan*/ *) ; 

TRef lj_opt_narrow_mod(jit_State *J, TRef rb, TRef rc, TValue *vb, TValue *vc)
{
  TRef tmp;
  rb = conv_str_tonum(J, rb, vb);
  rc = conv_str_tonum(J, rc, vc);
  if ((LJ_DUALNUM || (J->flags & JIT_F_OPT_NARROW)) &&
      tref_isinteger(rb) && tref_isinteger(rc) &&
      (tvisint(vc) ? intV(vc) != 0 : !tviszero(vc))) {
    emitir(IRTGI(IR_NE), rc, lj_ir_kint(J, 0));
    return emitir(IRTI(IR_MOD), rb, rc);
  }
  /* b % c ==> b - floor(b/c)*c */
  rb = lj_ir_tonum(J, rb);
  rc = lj_ir_tonum(J, rc);
  tmp = emitir(IRTN(IR_DIV), rb, rc);
  tmp = emitir(IRTN(IR_FPMATH), tmp, IRFPM_FLOOR);
  tmp = emitir(IRTN(IR_MUL), tmp, rc);
  return emitir(IRTN(IR_SUB), rb, tmp);
}