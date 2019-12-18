#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int /*<<< orphan*/ * top; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_19__ {int /*<<< orphan*/  threshold; } ;
struct TYPE_21__ {TYPE_2__ gc; } ;
typedef  TYPE_4__ global_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_18__ {int /*<<< orphan*/  gct; } ;
struct TYPE_22__ {TYPE_1__ gch; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_5__ GCobj ;
typedef  int /*<<< orphan*/  GCSize ;

/* Variables and functions */
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  LJ_MAX_MEM ; 
 int /*<<< orphan*/  copyTV (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hook_entergc (TYPE_4__*) ; 
 int /*<<< orphan*/  hook_restore (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_save (TYPE_4__*) ; 
 int /*<<< orphan*/  lj_err_throw (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lj_trace_abort (TYPE_4__*) ; 
 int lj_vm_pcall (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  setgcV (TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_call_finalizer(global_State *g, lua_State *L,
			      cTValue *mo, GCobj *o)
{
  /* Save and restore lots of state around the __gc callback. */
  uint8_t oldh = hook_save(g);
  GCSize oldt = g->gc.threshold;
  int errcode;
  TValue *top;
  lj_trace_abort(g);
  hook_entergc(g);  /* Disable hooks and new traces during __gc. */
  g->gc.threshold = LJ_MAX_MEM;  /* Prevent GC steps. */
  top = L->top;
  copyTV(L, top++, mo);
  if (LJ_FR2) setnilV(top++);
  setgcV(L, top, o, ~o->gch.gct);
  L->top = top+1;
  errcode = lj_vm_pcall(L, top, 1+0, -1);  /* Stack: |mo|o| -> | */
  hook_restore(g, oldh);
  g->gc.threshold = oldt;  /* Restore GC threshold. */
  if (errcode)
    lj_err_throw(L, errcode);  /* Propagate errors. */
}