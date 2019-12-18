#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t nsnap; int /*<<< orphan*/ * snapmap; TYPE_3__* snap; } ;
struct TYPE_7__ {TYPE_1__ cur; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_9__ {int /*<<< orphan*/  t; } ;
struct TYPE_8__ {size_t mapofs; size_t nent; } ;
typedef  TYPE_3__ SnapShot ;
typedef  size_t SnapNo ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  size_t MSize ;
typedef  scalar_t__ IRRef ;

/* Variables and functions */
 TYPE_5__* IR (scalar_t__) ; 
 scalar_t__ REF_FIRST ; 
 int /*<<< orphan*/  irt_setmark (int /*<<< orphan*/ ) ; 
 scalar_t__ snap_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_marksnap(jit_State *J)
{
  SnapNo i, nsnap = J->cur.nsnap;
  for (i = 0; i < nsnap; i++) {
    SnapShot *snap = &J->cur.snap[i];
    SnapEntry *map = &J->cur.snapmap[snap->mapofs];
    MSize n, nent = snap->nent;
    for (n = 0; n < nent; n++) {
      IRRef ref = snap_ref(map[n]);
      if (ref >= REF_FIRST)
	irt_setmark(IR(ref)->t);
    }
  }
}