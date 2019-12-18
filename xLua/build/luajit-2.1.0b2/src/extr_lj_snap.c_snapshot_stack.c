#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint16_t ;
struct TYPE_9__ {void* nsnapmap; scalar_t__ nins; int /*<<< orphan*/ * snapmap; } ;
struct TYPE_10__ {size_t baseslot; size_t maxslot; size_t framedepth; TYPE_1__ cur; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_11__ {scalar_t__ count; void* nslots; void* nent; scalar_t__ ref; void* mapofs; void* topslot; } ;
typedef  TYPE_3__ SnapShot ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  size_t MSize ;
typedef  scalar_t__ IRRef1 ;
typedef  size_t BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  lj_snap_grow_map (TYPE_2__*,size_t) ; 
 scalar_t__ snapshot_framelinks (TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t snapshot_slots (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void snapshot_stack(jit_State *J, SnapShot *snap, MSize nsnapmap)
{
  BCReg nslots = J->baseslot + J->maxslot;
  MSize nent;
  SnapEntry *p;
  /* Conservative estimate. */
  lj_snap_grow_map(J, nsnapmap + nslots + (MSize)J->framedepth+1);
  p = &J->cur.snapmap[nsnapmap];
  nent = snapshot_slots(J, p, nslots);
  snap->topslot = (uint8_t)snapshot_framelinks(J, p + nent);
  snap->mapofs = (uint16_t)nsnapmap;
  snap->ref = (IRRef1)J->cur.nins;
  snap->nent = (uint8_t)nent;
  snap->nslots = (uint8_t)nslots;
  snap->count = 0;
  J->cur.nsnapmap = (uint16_t)(nsnapmap + nent + 1 + J->framedepth);
}