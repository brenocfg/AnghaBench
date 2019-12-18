#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_15__ {scalar_t__ total; scalar_t__ estimate; int /*<<< orphan*/  root; int /*<<< orphan*/  sweep; scalar_t__ currentwhite; int /*<<< orphan*/  weak; int /*<<< orphan*/  grayagain; int /*<<< orphan*/  gray; } ;
struct TYPE_14__ {scalar_t__ marked; } ;
struct TYPE_16__ {TYPE_2__ gc; TYPE_1__ strempty; int /*<<< orphan*/  tmpbuf; } ;
typedef  TYPE_3__ global_State ;
typedef  scalar_t__ GCSize ;

/* Variables and functions */
 int /*<<< orphan*/  gc_clearweak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_mark_gcroot (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_mark_mmudata (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_mark_uv (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_markobj (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gc_propagate_gray (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_traverse_curtrace (TYPE_3__*) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iswhite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_buf_shrink (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t lj_gc_separateudata (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  mainthread (TYPE_3__*) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 scalar_t__ otherwhite (TYPE_3__*) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atomic(global_State *g, lua_State *L)
{
  size_t udsize;

  gc_mark_uv(g);  /* Need to remark open upvalues (the thread may be dead). */
  gc_propagate_gray(g);  /* Propagate any left-overs. */

  setgcrefr(g->gc.gray, g->gc.weak);  /* Empty the list of weak tables. */
  setgcrefnull(g->gc.weak);
  lua_assert(!iswhite(obj2gco(mainthread(g))));
  gc_markobj(g, L);  /* Mark running thread. */
  gc_traverse_curtrace(g);  /* Traverse current trace. */
  gc_mark_gcroot(g);  /* Mark GC roots (again). */
  gc_propagate_gray(g);  /* Propagate all of the above. */

  setgcrefr(g->gc.gray, g->gc.grayagain);  /* Empty the 2nd chance list. */
  setgcrefnull(g->gc.grayagain);
  gc_propagate_gray(g);  /* Propagate it. */

  udsize = lj_gc_separateudata(g, 0);  /* Separate userdata to be finalized. */
  gc_mark_mmudata(g);  /* Mark them. */
  udsize += gc_propagate_gray(g);  /* And propagate the marks. */

  /* All marking done, clear weak tables. */
  gc_clearweak(gcref(g->gc.weak));

  lj_buf_shrink(L, &g->tmpbuf);  /* Shrink temp buffer. */

  /* Prepare for sweep phase. */
  g->gc.currentwhite = (uint8_t)otherwhite(g);  /* Flip current white. */
  g->strempty.marked = g->gc.currentwhite;
  setmref(g->gc.sweep, &g->gc.root);
  g->gc.estimate = g->gc.total - (GCSize)udsize;  /* Initial estimate. */
}