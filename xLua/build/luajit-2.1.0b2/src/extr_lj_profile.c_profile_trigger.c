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
typedef  int uint8_t ;
struct TYPE_7__ {int hookmask; int vmstate; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_8__ {char vmstate; int /*<<< orphan*/  samples; TYPE_1__* g; } ;
typedef  TYPE_2__ ProfileState ;

/* Variables and functions */
 int HOOK_PROFILE ; 
 int HOOK_VMEVENT ; 
 int LJ_VMST_C ; 
 int LJ_VMST_GC ; 
 int LJ_VMST_INTERP ; 
 int /*<<< orphan*/  lj_dispatch_update (TYPE_1__*) ; 
 int /*<<< orphan*/  profile_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  profile_unlock (TYPE_2__*) ; 

__attribute__((used)) static void profile_trigger(ProfileState *ps)
{
  global_State *g = ps->g;
  uint8_t mask;
  profile_lock(ps);
  ps->samples++;  /* Always increment number of samples. */
  mask = g->hookmask;
  if (!(mask & (HOOK_PROFILE|HOOK_VMEVENT))) {  /* Set profile hook. */
    int st = g->vmstate;
    ps->vmstate = st >= 0 ? 'N' :
		  st == ~LJ_VMST_INTERP ? 'I' :
		  st == ~LJ_VMST_C ? 'C' :
		  st == ~LJ_VMST_GC ? 'G' : 'J';
    g->hookmask = (mask | HOOK_PROFILE);
    lj_dispatch_update(g);
  }
  profile_unlock(ps);
}