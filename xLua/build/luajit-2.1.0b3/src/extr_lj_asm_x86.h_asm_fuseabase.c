#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  ofs; } ;
struct TYPE_10__ {TYPE_1__ mrm; } ;
struct TYPE_9__ {scalar_t__ o; scalar_t__ op1; scalar_t__ op2; int /*<<< orphan*/  i; } ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (scalar_t__) ; 
 scalar_t__ IRFL_TAB_ARRAY ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_FLOAD ; 
 int /*<<< orphan*/  IR_NEWREF ; 
 scalar_t__ IR_TNEW ; 
 scalar_t__ LJ_MAX_COLOSIZE ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  neverfuse (TYPE_3__*) ; 
 scalar_t__ noconflict (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static IRRef asm_fuseabase(ASMState *as, IRRef ref)
{
  IRIns *irb = IR(ref);
  as->mrm.ofs = 0;
  if (irb->o == IR_FLOAD) {
    IRIns *ira = IR(irb->op1);
    lua_assert(irb->op2 == IRFL_TAB_ARRAY);
    /* We can avoid the FLOAD of t->array for colocated arrays. */
    if (ira->o == IR_TNEW && ira->op1 <= LJ_MAX_COLOSIZE &&
	!neverfuse(as) && noconflict(as, irb->op1, IR_NEWREF, 1)) {
      as->mrm.ofs = (int32_t)sizeof(GCtab);  /* Ofs to colocated array. */
      return irb->op1;  /* Table obj. */
    }
  } else if (irb->o == IR_ADD && irref_isk(irb->op2)) {
    /* Fuse base offset (vararg load). */
    as->mrm.ofs = IR(irb->op2)->i;
    return irb->op1;
  }
  return ref;  /* Otherwise use the given array base. */
}