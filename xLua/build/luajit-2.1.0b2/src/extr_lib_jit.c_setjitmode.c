#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_NOJIT ; 
 int LUAJIT_MODE_ALLFUNC ; 
 int LUAJIT_MODE_ALLSUBFUNC ; 
 int LUAJIT_MODE_ENGINE ; 
 int LUAJIT_MODE_FUNC ; 
 int LUAJIT_MODE_MASK ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 scalar_t__ boolV (scalar_t__) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_caller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int luaJIT_setmode (TYPE_1__*,int,int) ; 
 scalar_t__ tvisbool (scalar_t__) ; 
 scalar_t__ tvisfunc (scalar_t__) ; 
 scalar_t__ tvisnil (scalar_t__) ; 
 scalar_t__ tvisproto (scalar_t__) ; 
 int /*<<< orphan*/  tvistrue (scalar_t__) ; 

__attribute__((used)) static int setjitmode(lua_State *L, int mode)
{
  int idx = 0;
  if (L->base == L->top || tvisnil(L->base)) {  /* jit.on/off/flush([nil]) */
    mode |= LUAJIT_MODE_ENGINE;
  } else {
    /* jit.on/off/flush(func|proto, nil|true|false) */
    if (tvisfunc(L->base) || tvisproto(L->base))
      idx = 1;
    else if (!tvistrue(L->base))  /* jit.on/off/flush(true, nil|true|false) */
      goto err;
    if (L->base+1 < L->top && tvisbool(L->base+1))
      mode |= boolV(L->base+1) ? LUAJIT_MODE_ALLFUNC : LUAJIT_MODE_ALLSUBFUNC;
    else
      mode |= LUAJIT_MODE_FUNC;
  }
  if (luaJIT_setmode(L, idx, mode) != 1) {
    if ((mode & LUAJIT_MODE_MASK) == LUAJIT_MODE_ENGINE)
      lj_err_caller(L, LJ_ERR_NOJIT);
  err:
    lj_err_argt(L, 1, LUA_TFUNCTION);
  }
  return 0;
}