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
struct TYPE_8__ {int /*<<< orphan*/  ins; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  framesize; TYPE_3__* bcbase; } ;
struct TYPE_6__ {size_t sizebc; } ;
typedef  size_t MSize ;
typedef  TYPE_1__ GCproto ;
typedef  TYPE_2__ FuncState ;
typedef  TYPE_3__ BCInsLine ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  BCINS_AD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BC_FUNCF ; 
 int /*<<< orphan*/  BC_FUNCV ; 
 int PROTO_VARARG ; 

__attribute__((used)) static void fs_fixup_bc(FuncState *fs, GCproto *pt, BCIns *bc, MSize n)
{
  BCInsLine *base = fs->bcbase;
  MSize i;
  pt->sizebc = n;
  bc[0] = BCINS_AD((fs->flags & PROTO_VARARG) ? BC_FUNCV : BC_FUNCF,
		   fs->framesize, 0);
  for (i = 1; i < n; i++)
    bc[i] = base[i].ins;
}