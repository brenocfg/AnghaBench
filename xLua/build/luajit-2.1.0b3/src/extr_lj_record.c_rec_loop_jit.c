#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  traceno; } ;
struct TYPE_7__ {scalar_t__ parent; scalar_t__ exitno; scalar_t__ pc; scalar_t__ startpc; scalar_t__ framedepth; scalar_t__ retdepth; TYPE_1__ cur; scalar_t__ instunroll; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  TraceNo ;
typedef  scalar_t__ LoopEvent ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TRERR_LINNER ; 
 int /*<<< orphan*/  LJ_TRLINK_LOOP ; 
 int /*<<< orphan*/  LJ_TRLINK_ROOT ; 
 scalar_t__ LOOPEV_LEAVE ; 
 int /*<<< orphan*/  lj_record_stop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_loop_jit(jit_State *J, TraceNo lnk, LoopEvent ev)
{
  if (J->parent == 0 && J->exitno == 0) {  /* Root trace hit an inner loop. */
    /* Better let the inner loop spawn a side trace back here. */
    lj_trace_err(J, LJ_TRERR_LINNER);
  } else if (ev != LOOPEV_LEAVE) {  /* Side trace enters a compiled loop. */
    J->instunroll = 0;  /* Cannot continue across a compiled loop op. */
    if (J->pc == J->startpc && J->framedepth + J->retdepth == 0)
      lj_record_stop(J, LJ_TRLINK_LOOP, J->cur.traceno);  /* Form extra loop. */
    else
      lj_record_stop(J, LJ_TRLINK_ROOT, lnk);  /* Link to the loop. */
  }  /* Side trace continues across a loop that's left or not entered. */
}