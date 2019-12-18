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
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TRef ;
typedef  scalar_t__ IROp ;

/* Variables and functions */
 int /*<<< orphan*/  IRCONV_NUM_INT ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int) ; 
 int /*<<< orphan*/  IRTN (scalar_t__) ; 
 int /*<<< orphan*/  IRT_NUM ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_ADDOV ; 
 scalar_t__ IR_CONV ; 
 scalar_t__ IR_MUL ; 
 int /*<<< orphan*/  IR_STRTO ; 
 scalar_t__ IR_SUB ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strscan_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_vm_foldarith (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numberVnum (int /*<<< orphan*/ *) ; 
 scalar_t__ numisint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tref_isinteger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isstr (int /*<<< orphan*/ ) ; 

TRef lj_opt_narrow_arith(jit_State *J, TRef rb, TRef rc,
			 TValue *vb, TValue *vc, IROp op)
{
  if (tref_isstr(rb)) {
    rb = emitir(IRTG(IR_STRTO, IRT_NUM), rb, 0);
    lj_strscan_num(strV(vb), vb);
  }
  if (tref_isstr(rc)) {
    rc = emitir(IRTG(IR_STRTO, IRT_NUM), rc, 0);
    lj_strscan_num(strV(vc), vc);
  }
  /* Must not narrow MUL in non-DUALNUM variant, because it loses -0. */
  if ((op >= IR_ADD && op <= (LJ_DUALNUM ? IR_MUL : IR_SUB)) &&
      tref_isinteger(rb) && tref_isinteger(rc) &&
      numisint(lj_vm_foldarith(numberVnum(vb), numberVnum(vc),
			       (int)op - (int)IR_ADD)))
    return emitir(IRTGI((int)op - (int)IR_ADD + (int)IR_ADDOV), rb, rc);
  if (!tref_isnum(rb)) rb = emitir(IRTN(IR_CONV), rb, IRCONV_NUM_INT);
  if (!tref_isnum(rc)) rc = emitir(IRTN(IR_CONV), rc, IRCONV_NUM_INT);
  return emitir(IRTN(op), rb, rc);
}