#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_9__ {scalar_t__ top; int /*<<< orphan*/  ci; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  const TValue ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 scalar_t__ isLua (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaD_call (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  luaD_callnoyield (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  const* restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobj2s (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 

void luaT_callTM (lua_State *L, const TValue *f, const TValue *p1,
                  const TValue *p2, TValue *p3, int hasres) {
  ptrdiff_t result = savestack(L, p3);
  StkId func = L->top;
  setobj2s(L, func, f);  /* push function (assume EXTRA_STACK) */
  setobj2s(L, func + 1, p1);  /* 1st argument */
  setobj2s(L, func + 2, p2);  /* 2nd argument */
  L->top += 3;
  if (!hasres)  /* no result? 'p3' is third argument */
    setobj2s(L, L->top++, p3);  /* 3rd argument */
  /* metamethod may yield only when called from Lua code */
  if (isLua(L->ci))
    luaD_call(L, func, hasres);
  else
    luaD_callnoyield(L, func, hasres);
  if (hasres) {  /* if has result, move it to its place */
    p3 = restorestack(L, result);
    setobjs2s(L, p3, --L->top);
  }
}