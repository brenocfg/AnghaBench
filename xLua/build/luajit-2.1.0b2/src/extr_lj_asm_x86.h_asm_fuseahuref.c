#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_18__ {void* idx; scalar_t__ ofs; void* base; } ;
struct TYPE_22__ {TYPE_2__ mrm; } ;
struct TYPE_17__ {int /*<<< orphan*/ * uvptr; } ;
struct TYPE_21__ {TYPE_1__ l; } ;
struct TYPE_20__ {int /*<<< orphan*/  tv; } ;
struct TYPE_19__ {int op1; int op2; int /*<<< orphan*/  o; int /*<<< orphan*/  r; } ;
struct TYPE_16__ {TYPE_4__ uv; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int /*<<< orphan*/  Node ;
typedef  int IRRef ;
typedef  int /*<<< orphan*/  IROp ;
typedef  TYPE_3__ IRIns ;
typedef  TYPE_4__ GCupval ;
typedef  TYPE_5__ GCfunc ;
typedef  TYPE_6__ ASMState ;

/* Variables and functions */
 TYPE_3__* IR (int) ; 
#define  IR_AREF 130 
 int /*<<< orphan*/  IR_HREF ; 
#define  IR_HREFK 129 
 int /*<<< orphan*/  IR_KKPTR ; 
 int /*<<< orphan*/  IR_NEWREF ; 
#define  IR_UREFC 128 
 int /*<<< orphan*/  IR_UREFO ; 
 void* RID_NONE ; 
 int /*<<< orphan*/  asm_fusearef (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_11__* gcref (int /*<<< orphan*/ ) ; 
 TYPE_5__* ir_kfunc (TYPE_3__*) ; 
 int /*<<< orphan*/  irref_isk (int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  mayfuse (TYPE_6__*,int) ; 
 scalar_t__ ptr2addr (int /*<<< orphan*/ *) ; 
 scalar_t__ ra_alloc1 (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_fuseahuref(ASMState *as, IRRef ref, RegSet allow)
{
  IRIns *ir = IR(ref);
  if (ra_noreg(ir->r)) {
    switch ((IROp)ir->o) {
    case IR_AREF:
      if (mayfuse(as, ref)) {
	asm_fusearef(as, ir, allow);
	return;
      }
      break;
    case IR_HREFK:
      if (mayfuse(as, ref)) {
	as->mrm.base = (uint8_t)ra_alloc1(as, ir->op1, allow);
	as->mrm.ofs = (int32_t)(IR(ir->op2)->op2 * sizeof(Node));
	as->mrm.idx = RID_NONE;
	return;
      }
      break;
    case IR_UREFC:
      if (irref_isk(ir->op1)) {
	GCfunc *fn = ir_kfunc(IR(ir->op1));
	GCupval *uv = &gcref(fn->l.uvptr[(ir->op2 >> 8)])->uv;
	as->mrm.ofs = ptr2addr(&uv->tv);
	as->mrm.base = as->mrm.idx = RID_NONE;
	return;
      }
      break;
    default:
      lua_assert(ir->o == IR_HREF || ir->o == IR_NEWREF || ir->o == IR_UREFO ||
		 ir->o == IR_KKPTR);
      break;
    }
  }
  as->mrm.base = (uint8_t)ra_alloc1(as, ref, allow);
  as->mrm.ofs = 0;
  as->mrm.idx = RID_NONE;
}