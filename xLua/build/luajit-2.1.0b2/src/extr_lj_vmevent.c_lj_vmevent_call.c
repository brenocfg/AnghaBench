#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_11__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_12__ {scalar_t__ vmevmask; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (TYPE_1__*) ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 scalar_t__ VMEVENT_NOCACHE ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_restore (TYPE_2__*,scalar_t__) ; 
 scalar_t__ hook_save (TYPE_2__*) ; 
 int /*<<< orphan*/  hook_vmevent (TYPE_2__*) ; 
 int lj_vm_pcall (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strVdata (int /*<<< orphan*/ ) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ ) ; 

void lj_vmevent_call(lua_State *L, ptrdiff_t argbase)
{
  global_State *g = G(L);
  uint8_t oldmask = g->vmevmask;
  uint8_t oldh = hook_save(g);
  int status;
  g->vmevmask = 0;  /* Disable all events. */
  hook_vmevent(g);
  status = lj_vm_pcall(L, restorestack(L, argbase), 0+1, 0);
  if (LJ_UNLIKELY(status)) {
    /* Really shouldn't use stderr here, but where else to complain? */
    L->top--;
    fputs("VM handler failed: ", stderr);
    fputs(tvisstr(L->top) ? strVdata(L->top) : "?", stderr);
    fputc('\n', stderr);
  }
  hook_restore(g, oldh);
  if (g->vmevmask != VMEVENT_NOCACHE)
    g->vmevmask = oldmask;  /* Restore event mask, but not if not modified. */
}