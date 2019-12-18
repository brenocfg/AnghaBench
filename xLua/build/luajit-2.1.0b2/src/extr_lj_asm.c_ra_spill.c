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
typedef  int uint8_t ;
typedef  int int32_t ;
struct TYPE_6__ {int evenspill; int oddspill; int /*<<< orphan*/  J; TYPE_1__* ir; } ;
struct TYPE_5__ {int s; int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TRERR_SPILLOV ; 
 int REF_TRUE ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_hasspill (int) ; 
 int sps_scale (int) ; 

__attribute__((used)) static int32_t ra_spill(ASMState *as, IRIns *ir)
{
  int32_t slot = ir->s;
  lua_assert(ir >= as->ir + REF_TRUE);
  if (!ra_hasspill(slot)) {
    if (irt_is64(ir->t)) {
      slot = as->evenspill;
      as->evenspill += 2;
    } else if (as->oddspill) {
      slot = as->oddspill;
      as->oddspill = 0;
    } else {
      slot = as->evenspill;
      as->oddspill = slot+1;
      as->evenspill += 2;
    }
    if (as->evenspill > 256)
      lj_trace_err(as->J, LJ_TRERR_SPILLOV);
    ir->s = (uint8_t)slot;
  }
  return sps_scale(slot);
}