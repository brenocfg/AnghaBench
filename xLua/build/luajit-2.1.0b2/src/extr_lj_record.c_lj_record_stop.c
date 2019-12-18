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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {scalar_t__ traceno; scalar_t__ root; scalar_t__ link; scalar_t__ linktype; } ;
struct TYPE_9__ {scalar_t__ framedepth; scalar_t__ retdepth; int flags; int mergesnap; scalar_t__ needsnap; TYPE_1__ cur; scalar_t__ retryrec; } ;
typedef  TYPE_2__ jit_State ;
typedef  scalar_t__ TraceNo ;
typedef  scalar_t__ TraceLink ;

/* Variables and functions */
 int JIT_F_OPT_LOOP ; 
 int /*<<< orphan*/  LJ_TRERR_RETRY ; 
 int /*<<< orphan*/  canonicalize_slots (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_snap_add (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_trace_end (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 

void lj_record_stop(jit_State *J, TraceLink linktype, TraceNo lnk)
{
#ifdef LUAJIT_ENABLE_TABLE_BUMP
  if (J->retryrec)
    lj_trace_err(J, LJ_TRERR_RETRY);
#endif
  lj_trace_end(J);
  J->cur.linktype = (uint8_t)linktype;
  J->cur.link = (uint16_t)lnk;
  /* Looping back at the same stack level? */
  if (lnk == J->cur.traceno && J->framedepth + J->retdepth == 0) {
    if ((J->flags & JIT_F_OPT_LOOP))  /* Shall we try to create a loop? */
      goto nocanon;  /* Do not canonicalize or we lose the narrowing. */
    if (J->cur.root)  /* Otherwise ensure we always link to the root trace. */
      J->cur.link = J->cur.root;
  }
  canonicalize_slots(J);
nocanon:
  /* Note: all loop ops must set J->pc to the following instruction! */
  lj_snap_add(J);  /* Add loop snapshot. */
  J->needsnap = 0;
  J->mergesnap = 1;  /* In case recording continues. */
}