#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int nsnap; int /*<<< orphan*/ * snap; } ;
struct TYPE_9__ {int const flags; scalar_t__ loopref; TYPE_1__ cur; scalar_t__* chain; } ;
typedef  TYPE_2__ jit_State ;

/* Variables and functions */
 size_t IR_CNEW ; 
 size_t IR_CNEWI ; 
 size_t IR_TDUP ; 
 size_t IR_TNEW ; 
 int JIT_F_OPT_CSE ; 
 int JIT_F_OPT_DCE ; 
 int JIT_F_OPT_FOLD ; 
 int JIT_F_OPT_FWD ; 
 int JIT_F_OPT_SINK ; 
 scalar_t__ LJ_HASFFI ; 
 int /*<<< orphan*/  sink_mark_ins (TYPE_2__*) ; 
 int /*<<< orphan*/  sink_mark_snap (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sink_remark_phi (TYPE_2__*) ; 
 int /*<<< orphan*/  sink_sweep_ins (TYPE_2__*) ; 

void lj_opt_sink(jit_State *J)
{
  const uint32_t need = (JIT_F_OPT_SINK|JIT_F_OPT_FWD|
			 JIT_F_OPT_DCE|JIT_F_OPT_CSE|JIT_F_OPT_FOLD);
  if ((J->flags & need) == need &&
      (J->chain[IR_TNEW] || J->chain[IR_TDUP] ||
       (LJ_HASFFI && (J->chain[IR_CNEW] || J->chain[IR_CNEWI])))) {
    if (!J->loopref)
      sink_mark_snap(J, &J->cur.snap[J->cur.nsnap-1]);
    sink_mark_ins(J);
    if (J->loopref)
      sink_remark_phi(J);
    sink_sweep_ins(J);
  }
}