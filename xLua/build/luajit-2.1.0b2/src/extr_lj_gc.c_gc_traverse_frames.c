#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  maxstack; int /*<<< orphan*/ * base; int /*<<< orphan*/  stack; int /*<<< orphan*/ * top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_5__ {int /*<<< orphan*/  framesize; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  MSize ;
typedef  int /*<<< orphan*/  GCfunc ;

/* Variables and functions */
 int LJ_FR2 ; 
 int /*<<< orphan*/ * frame_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prev (int /*<<< orphan*/ *) ; 
 TYPE_3__* funcproto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_markobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isluafunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MSize gc_traverse_frames(global_State *g, lua_State *th)
{
  TValue *frame, *top = th->top-1, *bot = tvref(th->stack);
  /* Note: extra vararg frame not skipped, marks function twice (harmless). */
  for (frame = th->base-1; frame > bot+LJ_FR2; frame = frame_prev(frame)) {
    GCfunc *fn = frame_func(frame);
    TValue *ftop = frame;
    if (isluafunc(fn)) ftop += funcproto(fn)->framesize;
    if (ftop > top) top = ftop;
    if (!LJ_FR2) gc_markobj(g, fn);  /* Need to mark hidden function (or L). */
  }
  top++;  /* Correct bias of -1 (frame == base-1). */
  if (top > tvref(th->maxstack)) top = tvref(th->maxstack);
  return (MSize)(top - bot);  /* Return minimum needed stack size. */
}