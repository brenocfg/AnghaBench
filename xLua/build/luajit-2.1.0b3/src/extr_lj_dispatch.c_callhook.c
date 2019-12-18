#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int base; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  (* lua_Hook ) (TYPE_1__*,TYPE_3__*) ;
struct TYPE_18__ {int event; int i_ci; int /*<<< orphan*/  currentline; } ;
typedef  TYPE_3__ lua_Debug ;
struct TYPE_19__ {int /*<<< orphan*/  cur_L; int /*<<< orphan*/  (* hookf ) (TYPE_1__*,TYPE_3__*) ;} ;
typedef  TYPE_5__ global_State ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 TYPE_5__* G (TYPE_1__*) ; 
 scalar_t__ LUA_MINSTACK ; 
 int /*<<< orphan*/  hook_active (TYPE_5__*) ; 
 int /*<<< orphan*/  hook_enter (TYPE_5__*) ; 
 int /*<<< orphan*/  hook_leave (TYPE_5__*) ; 
 int /*<<< orphan*/  lj_profile_hook_enter (TYPE_5__*) ; 
 int /*<<< orphan*/  lj_profile_hook_leave (TYPE_5__*) ; 
 int /*<<< orphan*/  lj_state_checkstack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_trace_abort (TYPE_5__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (TYPE_1__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void callhook(lua_State *L, int event, BCLine line)
{
  global_State *g = G(L);
  lua_Hook hookf = g->hookf;
  if (hookf && !hook_active(g)) {
    lua_Debug ar;
    lj_trace_abort(g);  /* Abort recording on any hook call. */
    ar.event = event;
    ar.currentline = line;
    /* Top frame, nextframe = NULL. */
    ar.i_ci = (int)((L->base-1) - tvref(L->stack));
    lj_state_checkstack(L, 1+LUA_MINSTACK);
#if LJ_HASPROFILE && !LJ_PROFILE_SIGPROF
    lj_profile_hook_enter(g);
#else
    hook_enter(g);
#endif
    hookf(L, &ar);
    lua_assert(hook_active(g));
    setgcref(g->cur_L, obj2gco(L));
#if LJ_HASPROFILE && !LJ_PROFILE_SIGPROF
    lj_profile_hook_leave(g);
#else
    hook_leave(g);
#endif
  }
}