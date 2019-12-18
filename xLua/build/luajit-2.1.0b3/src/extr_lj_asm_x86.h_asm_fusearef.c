#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_10__ {int ofs; void* idx; int /*<<< orphan*/  scale; void* base; } ;
struct TYPE_12__ {TYPE_1__ mrm; } ;
struct TYPE_11__ {scalar_t__ o; int i; int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_AREF ; 
 int /*<<< orphan*/  LJ_64 ; 
 void* RID_NONE ; 
 int /*<<< orphan*/  XM_SCALE8 ; 
 int /*<<< orphan*/  asm_fuseabase (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ mayfuse (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_alloc1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void asm_fusearef(ASMState *as, IRIns *ir, RegSet allow)
{
  IRIns *irx;
  lua_assert(ir->o == IR_AREF);
  as->mrm.base = (uint8_t)ra_alloc1(as, asm_fuseabase(as, ir->op1), allow);
  irx = IR(ir->op2);
  if (irref_isk(ir->op2)) {
    as->mrm.ofs += 8*irx->i;
    as->mrm.idx = RID_NONE;
  } else {
    rset_clear(allow, as->mrm.base);
    as->mrm.scale = XM_SCALE8;
    /* Fuse a constant ADD (e.g. t[i+1]) into the offset.
    ** Doesn't help much without ABCelim, but reduces register pressure.
    */
    if (!LJ_64 &&  /* Has bad effects with negative index on x64. */
	mayfuse(as, ir->op2) && ra_noreg(irx->r) &&
	irx->o == IR_ADD && irref_isk(irx->op2)) {
      as->mrm.ofs += 8*IR(irx->op2)->i;
      as->mrm.idx = (uint8_t)ra_alloc1(as, irx->op1, allow);
    } else {
      as->mrm.idx = (uint8_t)ra_alloc1(as, ir->op2, allow);
    }
  }
}