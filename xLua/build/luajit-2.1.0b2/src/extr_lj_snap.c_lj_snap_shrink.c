#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_6__ {int nsnap; size_t nsnapmap; int /*<<< orphan*/ * snapmap; TYPE_3__* snap; } ;
struct TYPE_7__ {scalar_t__ maxslot; scalar_t__ baseslot; TYPE_1__ cur; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_8__ {size_t mapofs; size_t nent; scalar_t__ nslots; } ;
typedef  TYPE_3__ SnapShot ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  size_t MSize ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int SNAP_USEDEF_SLOTS ; 
 int /*<<< orphan*/  snap_pc (int /*<<< orphan*/ ) ; 
 scalar_t__ snap_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ snap_usedef (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

void lj_snap_shrink(jit_State *J)
{
  SnapShot *snap = &J->cur.snap[J->cur.nsnap-1];
  SnapEntry *map = &J->cur.snapmap[snap->mapofs];
  MSize n, m, nlim, nent = snap->nent;
  uint8_t udf[SNAP_USEDEF_SLOTS];
  BCReg maxslot = J->maxslot;
  BCReg minslot = snap_usedef(J, udf, snap_pc(map[nent]), maxslot);
  BCReg baseslot = J->baseslot;
  maxslot += baseslot;
  minslot += baseslot;
  snap->nslots = (uint8_t)maxslot;
  for (n = m = 0; n < nent; n++) {  /* Remove unused slots from snapshot. */
    BCReg s = snap_slot(map[n]);
    if (s < minslot || (s < maxslot && udf[s-baseslot] == 0))
      map[m++] = map[n];  /* Only copy used slots. */
  }
  snap->nent = (uint8_t)m;
  nlim = J->cur.nsnapmap - snap->mapofs - 1;
  while (n <= nlim) map[m++] = map[n++];  /* Move PC + frame links down. */
  J->cur.nsnapmap = (uint16_t)(snap->mapofs + m);  /* Free up space in map. */
}