#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;

/* Variables and functions */
 int LJ_FR2 ; 
 scalar_t__ frame_gc (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_islua (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_isvarg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevl (int /*<<< orphan*/ *) ; 
 scalar_t__ obj2gco (TYPE_1__*) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

cTValue *lj_debug_frame(lua_State *L, int level, int *size)
{
  cTValue *frame, *nextframe, *bot = tvref(L->stack)+LJ_FR2;
  /* Traverse frames backwards. */
  for (nextframe = frame = L->base-1; frame > bot; ) {
    if (frame_gc(frame) == obj2gco(L))
      level++;  /* Skip dummy frames. See lj_err_optype_call(). */
    if (level-- == 0) {
      *size = (int)(nextframe - frame);
      return frame;  /* Level found. */
    }
    nextframe = frame;
    if (frame_islua(frame)) {
      frame = frame_prevl(frame);
    } else {
      if (frame_isvarg(frame))
	level++;  /* Skip vararg pseudo-frame. */
      frame = frame_prevd(frame);
    }
  }
  *size = level;
  return NULL;  /* Level not found. */
}