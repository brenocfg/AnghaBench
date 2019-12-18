#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  traceno; } ;
struct TYPE_11__ {scalar_t__ framedepth; scalar_t__ retdepth; TYPE_1__ cur; int /*<<< orphan*/ * startpc; int /*<<< orphan*/ * pc; scalar_t__ instunroll; int /*<<< orphan*/ * patchpc; int /*<<< orphan*/  patchins; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  TraceNo ;
struct TYPE_12__ {scalar_t__ linktype; int /*<<< orphan*/  startins; } ;
typedef  TYPE_3__ GCtrace ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ LJ_TRLINK_RETURN ; 
 int /*<<< orphan*/  LJ_TRLINK_ROOT ; 
 int /*<<< orphan*/  LJ_TRLINK_TAILREC ; 
 int /*<<< orphan*/  check_call_unroll (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_record_stop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rec_func_setup (TYPE_2__*) ; 
 TYPE_3__* traceref (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_func_jit(jit_State *J, TraceNo lnk)
{
  GCtrace *T;
  rec_func_setup(J);
  T = traceref(J, lnk);
  if (T->linktype == LJ_TRLINK_RETURN) {  /* Trace returns to interpreter? */
    check_call_unroll(J, lnk);
    /* Temporarily unpatch JFUNC* to continue recording across function. */
    J->patchins = *J->pc;
    J->patchpc = (BCIns *)J->pc;
    *J->patchpc = T->startins;
    return;
  }
  J->instunroll = 0;  /* Cannot continue across a compiled function. */
  if (J->pc == J->startpc && J->framedepth + J->retdepth == 0)
    lj_record_stop(J, LJ_TRLINK_TAILREC, J->cur.traceno);  /* Extra tail-rec. */
  else
    lj_record_stop(J, LJ_TRLINK_ROOT, lnk);  /* Link to the function. */
}