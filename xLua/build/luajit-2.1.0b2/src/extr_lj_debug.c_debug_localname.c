#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/ * top; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_10__ {scalar_t__ i_ci; } ;
typedef  TYPE_2__ lua_Debug ;
struct TYPE_11__ {int flags; int numparams; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ GCproto ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  int BCReg ;
typedef  scalar_t__ BCPos ;

/* Variables and functions */
 int LJ_FR2 ; 
 scalar_t__ NO_BCPOS ; 
 int PROTO_VARARG ; 
 scalar_t__ debug_framepc (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* debug_varname (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/ * frame_func (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_isvarg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevd (int /*<<< orphan*/ *) ; 
 TYPE_3__* funcproto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TValue *debug_localname(lua_State *L, const lua_Debug *ar,
			       const char **name, BCReg slot1)
{
  uint32_t offset = (uint32_t)ar->i_ci & 0xffff;
  uint32_t size = (uint32_t)ar->i_ci >> 16;
  TValue *frame = tvref(L->stack) + offset;
  TValue *nextframe = size ? frame + size : NULL;
  GCfunc *fn = frame_func(frame);
  BCPos pc = debug_framepc(L, fn, nextframe);
  if (!nextframe) nextframe = L->top+LJ_FR2;
  if ((int)slot1 < 0) {  /* Negative slot number is for varargs. */
    if (pc != NO_BCPOS) {
      GCproto *pt = funcproto(fn);
      if ((pt->flags & PROTO_VARARG)) {
	slot1 = pt->numparams + (BCReg)(-(int)slot1);
	if (frame_isvarg(frame)) {  /* Vararg frame has been set up? (pc!=0) */
	  nextframe = frame;
	  frame = frame_prevd(frame);
	}
	if (frame + slot1+LJ_FR2 < nextframe) {
	  *name = "(*vararg)";
	  return frame+slot1;
	}
      }
    }
    return NULL;
  }
  if (pc != NO_BCPOS &&
      (*name = debug_varname(funcproto(fn), pc, slot1-1)) != NULL)
    ;
  else if (slot1 > 0 && frame + slot1+LJ_FR2 < nextframe)
    *name = "(*temporary)";
  return frame+slot1;
}