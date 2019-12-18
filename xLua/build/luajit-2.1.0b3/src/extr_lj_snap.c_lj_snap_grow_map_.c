#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * snapmap; } ;
struct TYPE_5__ {int sizesnapmap; int /*<<< orphan*/ * snapmapbuf; TYPE_1__ cur; int /*<<< orphan*/  L; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  int MSize ;

/* Variables and functions */
 scalar_t__ lj_mem_realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

void lj_snap_grow_map_(jit_State *J, MSize need)
{
  if (need < 2*J->sizesnapmap)
    need = 2*J->sizesnapmap;
  else if (need < 64)
    need = 64;
  J->snapmapbuf = (SnapEntry *)lj_mem_realloc(J->L, J->snapmapbuf,
		    J->sizesnapmap*sizeof(SnapEntry), need*sizeof(SnapEntry));
  J->cur.snapmap = J->snapmapbuf;
  J->sizesnapmap = need;
}