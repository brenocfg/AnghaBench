#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int baseslot; int maxslot; int /*<<< orphan*/ * slot; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {scalar_t__ o; int op2; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  TYPE_2__ IRIns ;
typedef  int BCReg ;

/* Variables and functions */
 TYPE_2__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRCONV_NUM_INT ; 
 int IRSLOAD_READONLY ; 
 int /*<<< orphan*/  IRTN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IR_CONV ; 
 scalar_t__ IR_SLOAD ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isinteger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void canonicalize_slots(jit_State *J)
{
  BCReg s;
  if (LJ_DUALNUM) return;
  for (s = J->baseslot+J->maxslot-1; s >= 1; s--) {
    TRef tr = J->slot[s];
    if (tref_isinteger(tr)) {
      IRIns *ir = IR(tref_ref(tr));
      if (!(ir->o == IR_SLOAD && (ir->op2 & IRSLOAD_READONLY)))
	J->slot[s] = emitir(IRTN(IR_CONV), tr, IRCONV_NUM_INT);
    }
  }
}