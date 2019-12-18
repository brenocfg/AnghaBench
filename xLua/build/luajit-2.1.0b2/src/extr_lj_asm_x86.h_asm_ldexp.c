#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; int /*<<< orphan*/  r; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  RID_ESP ; 
 int /*<<< orphan*/  XI_FPOP1 ; 
 int /*<<< orphan*/  XI_FSCALE ; 
 int /*<<< orphan*/  XO_FSTPq ; 
 int /*<<< orphan*/  XO_MOVSD ; 
 int /*<<< orphan*/  XOg_FSTPq ; 
 int /*<<< orphan*/  asm_x87load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rmro (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_x87op (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_modified (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sps_scale (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_ldexp(ASMState *as, IRIns *ir)
{
  int32_t ofs = sps_scale(ir->s);  /* Use spill slot or temp slots. */
  Reg dest = ir->r;
  if (ra_hasreg(dest)) {
    ra_free(as, dest);
    ra_modified(as, dest);
    emit_rmro(as, XO_MOVSD, dest, RID_ESP, ofs);
  }
  emit_rmro(as, XO_FSTPq, XOg_FSTPq, RID_ESP, ofs);
  emit_x87op(as, XI_FPOP1);
  emit_x87op(as, XI_FSCALE);
  asm_x87load(as, ir->op1);
  asm_x87load(as, ir->op2);
}