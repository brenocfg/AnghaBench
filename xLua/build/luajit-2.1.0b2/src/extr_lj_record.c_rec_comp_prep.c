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
struct TYPE_7__ {int nsnap; scalar_t__ nins; TYPE_1__* snap; } ;
struct TYPE_8__ {TYPE_2__ cur; } ;
typedef  TYPE_3__ jit_State ;
struct TYPE_6__ {scalar_t__ ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IR_NOP ; 
 int /*<<< orphan*/  emitir_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_snap_add (TYPE_3__*) ; 

__attribute__((used)) static void rec_comp_prep(jit_State *J)
{
  /* Prevent merging with snapshot #0 (GC exit) since we fixup the PC. */
  if (J->cur.nsnap == 1 && J->cur.snap[0].ref == J->cur.nins)
    emitir_raw(IRT(IR_NOP, IRT_NIL), 0, 0);
  lj_snap_add(J);
}