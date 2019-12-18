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
struct TYPE_4__ {float prof_mode; int /*<<< orphan*/ * prev_pt; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IR_PROF ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_snap_add (TYPE_1__*) ; 

__attribute__((used)) static void rec_profile_ret(jit_State *J)
{
  if (J->prof_mode == 'f') {
    emitir(IRTG(IR_PROF, IRT_NIL), 0, 0);
    J->prev_pt = NULL;
    lj_snap_add(J);
  }
}