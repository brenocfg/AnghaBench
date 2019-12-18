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
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/  baseslot; int /*<<< orphan*/  base; int /*<<< orphan*/  framedepth; } ;
typedef  TYPE_1__ jit_State ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  rec_call_setup (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

void lj_record_call(jit_State *J, BCReg func, ptrdiff_t nargs)
{
  rec_call_setup(J, func, nargs);
  /* Bump frame. */
  J->framedepth++;
  J->base += func+1;
  J->baseslot += func+1;
}