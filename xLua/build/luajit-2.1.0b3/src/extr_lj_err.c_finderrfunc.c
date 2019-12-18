#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_8__ {void* cframe; int /*<<< orphan*/  stack; int /*<<< orphan*/ * base; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_7__ {int /*<<< orphan*/  ffid; } ;
struct TYPE_9__ {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_xpcall ; 
#define  FRAME_C 135 
#define  FRAME_CONT 134 
#define  FRAME_CP 133 
#define  FRAME_LUA 132 
#define  FRAME_LUAP 131 
#define  FRAME_PCALL 130 
#define  FRAME_PCALLH 129 
#define  FRAME_VARG 128 
 int LJ_FR2 ; 
 int /*<<< orphan*/  cframe_canyield (void*) ; 
 scalar_t__ cframe_errfunc (void*) ; 
 int /*<<< orphan*/  cframe_nres (void*) ; 
 void* cframe_prev (void*) ; 
 void* cframe_raw (void*) ; 
 TYPE_5__* frame_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_iscont_fficb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevl (int /*<<< orphan*/ *) ; 
 int frame_typep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * restorestack (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ savestack (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptrdiff_t finderrfunc(lua_State *L)
{
  cTValue *frame = L->base-1, *bot = tvref(L->stack)+LJ_FR2;
  void *cf = L->cframe;
  while (frame > bot && cf) {
    while (cframe_nres(cframe_raw(cf)) < 0) {  /* cframe without frame? */
      if (frame >= restorestack(L, -cframe_nres(cf)))
	break;
      if (cframe_errfunc(cf) >= 0)  /* Error handler not inherited (-1)? */
	return cframe_errfunc(cf);
      cf = cframe_prev(cf);  /* Else unwind cframe and continue searching. */
      if (cf == NULL)
	return 0;
    }
    switch (frame_typep(frame)) {
    case FRAME_LUA:
    case FRAME_LUAP:
      frame = frame_prevl(frame);
      break;
    case FRAME_C:
      cf = cframe_prev(cf);
      /* fallthrough */
    case FRAME_VARG:
      frame = frame_prevd(frame);
      break;
    case FRAME_CONT:
      if (frame_iscont_fficb(frame))
	cf = cframe_prev(cf);
      frame = frame_prevd(frame);
      break;
    case FRAME_CP:
      if (cframe_canyield(cf)) return 0;
      if (cframe_errfunc(cf) >= 0)
	return cframe_errfunc(cf);
      frame = frame_prevd(frame);
      break;
    case FRAME_PCALL:
    case FRAME_PCALLH:
      if (frame_func(frame_prevd(frame))->c.ffid == FF_xpcall)
	return savestack(L, frame_prevd(frame)+1);  /* xpcall's errorfunc. */
      return 0;
    default:
      lua_assert(0);
      return 0;
    }
  }
  return 0;
}