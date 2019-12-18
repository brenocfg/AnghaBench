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
struct TYPE_7__ {int nins; int /*<<< orphan*/  traceno; } ;
struct TYPE_8__ {scalar_t__ parent; scalar_t__ exitno; scalar_t__ framedepth; scalar_t__ retdepth; int loopref; scalar_t__ loopunroll; TYPE_1__ cur; int /*<<< orphan*/  const* startpc; } ;
typedef  TYPE_2__ jit_State ;
typedef  scalar_t__ LoopEvent ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TRERR_LINNER ; 
 int /*<<< orphan*/  LJ_TRERR_LLEAVE ; 
 int /*<<< orphan*/  LJ_TRERR_LUNROLL ; 
 int /*<<< orphan*/  LJ_TRLINK_LOOP ; 
 scalar_t__ LOOPEV_ENTERLO ; 
 scalar_t__ LOOPEV_LEAVE ; 
 int bc_j (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  innerloopleft (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lj_record_stop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_loop_interp(jit_State *J, const BCIns *pc, LoopEvent ev)
{
  if (J->parent == 0 && J->exitno == 0) {
    if (pc == J->startpc && J->framedepth + J->retdepth == 0) {
      /* Same loop? */
      if (ev == LOOPEV_LEAVE)  /* Must loop back to form a root trace. */
	lj_trace_err(J, LJ_TRERR_LLEAVE);
      lj_record_stop(J, LJ_TRLINK_LOOP, J->cur.traceno);  /* Looping trace. */
    } else if (ev != LOOPEV_LEAVE) {  /* Entering inner loop? */
      /* It's usually better to abort here and wait until the inner loop
      ** is traced. But if the inner loop repeatedly didn't loop back,
      ** this indicates a low trip count. In this case try unrolling
      ** an inner loop even in a root trace. But it's better to be a bit
      ** more conservative here and only do it for very short loops.
      */
      if (bc_j(*pc) != -1 && !innerloopleft(J, pc))
	lj_trace_err(J, LJ_TRERR_LINNER);  /* Root trace hit an inner loop. */
      if ((ev != LOOPEV_ENTERLO &&
	   J->loopref && J->cur.nins - J->loopref > 24) || --J->loopunroll < 0)
	lj_trace_err(J, LJ_TRERR_LUNROLL);  /* Limit loop unrolling. */
      J->loopref = J->cur.nins;
    }
  } else if (ev != LOOPEV_LEAVE) {  /* Side trace enters an inner loop. */
    J->loopref = J->cur.nins;
    if (--J->loopunroll < 0)
      lj_trace_err(J, LJ_TRERR_LUNROLL);  /* Limit loop unrolling. */
  }  /* Side trace continues across a loop that's left or not entered. */
}