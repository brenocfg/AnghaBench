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
struct TYPE_5__ {int maxslot; scalar_t__ baseslot; int /*<<< orphan*/ * base; int /*<<< orphan*/  framedepth; TYPE_2__* pt; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {int flags; scalar_t__ framesize; scalar_t__ numparams; } ;
typedef  TYPE_2__ GCproto ;
typedef  int BCReg ;

/* Variables and functions */
 scalar_t__ LJ_MAX_JSLOTS ; 
 int /*<<< orphan*/  LJ_TRERR_STACKOV ; 
 int PROTO_VARARG ; 
 int /*<<< orphan*/  TREF_NIL ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void rec_func_vararg(jit_State *J)
{
  GCproto *pt = J->pt;
  BCReg s, fixargs, vframe = J->maxslot+1;
  lua_assert((pt->flags & PROTO_VARARG));
  if (J->baseslot + vframe + pt->framesize >= LJ_MAX_JSLOTS)
    lj_trace_err(J, LJ_TRERR_STACKOV);
  J->base[vframe-1] = J->base[-1];  /* Copy function up. */
  /* Copy fixarg slots up and set their original slots to nil. */
  fixargs = pt->numparams < J->maxslot ? pt->numparams : J->maxslot;
  for (s = 0; s < fixargs; s++) {
    J->base[vframe+s] = J->base[s];
    J->base[s] = TREF_NIL;
  }
  J->maxslot = fixargs;
  J->framedepth++;
  J->base += vframe;
  J->baseslot += vframe;
}