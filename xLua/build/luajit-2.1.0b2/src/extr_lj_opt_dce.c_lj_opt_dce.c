#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  bpropcache; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 int JIT_F_OPT_DCE ; 
 int /*<<< orphan*/  dce_marksnap (TYPE_1__*) ; 
 int /*<<< orphan*/  dce_propagate (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void lj_opt_dce(jit_State *J)
{
  if ((J->flags & JIT_F_OPT_DCE)) {
    dce_marksnap(J);
    dce_propagate(J);
    memset(J->bpropcache, 0, sizeof(J->bpropcache));  /* Invalidate cache. */
  }
}