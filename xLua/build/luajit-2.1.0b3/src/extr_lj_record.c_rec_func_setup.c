#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ baseslot; size_t maxslot; int /*<<< orphan*/ * base; TYPE_2__* pt; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {size_t numparams; int flags; scalar_t__ framesize; } ;
typedef  TYPE_2__ GCproto ;
typedef  size_t BCReg ;

/* Variables and functions */
 scalar_t__ LJ_MAX_JSLOTS ; 
 int /*<<< orphan*/  LJ_TRERR_CJITOFF ; 
 int /*<<< orphan*/  LJ_TRERR_STACKOV ; 
 int PROTO_NOJIT ; 
 int /*<<< orphan*/  TREF_NIL ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_func_setup(jit_State *J)
{
  GCproto *pt = J->pt;
  BCReg s, numparams = pt->numparams;
  if ((pt->flags & PROTO_NOJIT))
    lj_trace_err(J, LJ_TRERR_CJITOFF);
  if (J->baseslot + pt->framesize >= LJ_MAX_JSLOTS)
    lj_trace_err(J, LJ_TRERR_STACKOV);
  /* Fill up missing parameters with nil. */
  for (s = J->maxslot; s < numparams; s++)
    J->base[s] = TREF_NIL;
  /* The remaining slots should never be read before they are written. */
  J->maxslot = numparams;
}