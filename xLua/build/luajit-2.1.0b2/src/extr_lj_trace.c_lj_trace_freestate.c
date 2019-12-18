#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_7__ {scalar_t__ traceno; } ;
struct TYPE_8__ {scalar_t__ sizetrace; scalar_t__ trace; scalar_t__ irbotlim; scalar_t__ irtoplim; scalar_t__ irbuf; scalar_t__ sizesnap; scalar_t__ snapbuf; scalar_t__ sizesnapmap; scalar_t__ snapmapbuf; TYPE_1__ cur; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  global_State ;

/* Variables and functions */
 TYPE_2__* G2J (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCRef ; 
 int /*<<< orphan*/  IRIns ; 
 int /*<<< orphan*/  SnapEntry ; 
 int /*<<< orphan*/  SnapShot ; 
 int /*<<< orphan*/  lj_ir_k64_freeall (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_mcode_free (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_mem_freevec (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * traceref (TYPE_2__*,int) ; 

void lj_trace_freestate(global_State *g)
{
  jit_State *J = G2J(g);
#ifdef LUA_USE_ASSERT
  {  /* This assumes all traces have already been freed. */
    ptrdiff_t i;
    for (i = 1; i < (ptrdiff_t)J->sizetrace; i++)
      lua_assert(i == (ptrdiff_t)J->cur.traceno || traceref(J, i) == NULL);
  }
#endif
  lj_mcode_free(J);
  lj_ir_k64_freeall(J);
  lj_mem_freevec(g, J->snapmapbuf, J->sizesnapmap, SnapEntry);
  lj_mem_freevec(g, J->snapbuf, J->sizesnap, SnapShot);
  lj_mem_freevec(g, J->irbuf + J->irbotlim, J->irtoplim - J->irbotlim, IRIns);
  lj_mem_freevec(g, J->trace, J->sizetrace, GCRef);
}