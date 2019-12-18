#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {size_t maxslot; scalar_t__* base; int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ jit_State ;
typedef  size_t BCReg ;

/* Variables and functions */
 int SNAP_USEDEF_SLOTS ; 
 size_t snap_usedef (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

void lj_snap_purge(jit_State *J)
{
  uint8_t udf[SNAP_USEDEF_SLOTS];
  BCReg maxslot = J->maxslot;
  BCReg s = snap_usedef(J, udf, J->pc, maxslot);
  for (; s < maxslot; s++)
    if (udf[s] != 0)
      J->base[s] = 0;  /* Purge dead slots. */
}