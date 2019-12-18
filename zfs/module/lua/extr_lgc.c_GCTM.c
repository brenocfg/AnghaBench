#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ top; int /*<<< orphan*/  allowhook; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_15__ {int gcrunning; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  const TValue ;

/* Variables and functions */
 TYPE_2__* G (TYPE_1__*) ; 
 int LUA_ERRGCMM ; 
 int LUA_ERRRUN ; 
 int LUA_OK ; 
 int /*<<< orphan*/  TM_GC ; 
 int /*<<< orphan*/  dothecall ; 
 int luaD_pcall (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaD_throw (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaO_pushfstring (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  const* luaT_gettmbyobj (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setgcovalue (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj2s (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*) ; 
 char* svalue (scalar_t__) ; 
 scalar_t__ ttisfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (scalar_t__) ; 
 int /*<<< orphan*/  udata2finalize (TYPE_2__*) ; 

__attribute__((used)) static void GCTM (lua_State *L, int propagateerrors) {
  global_State *g = G(L);
  const TValue *tm;
  TValue v;
  setgcovalue(L, &v, udata2finalize(g));
  tm = luaT_gettmbyobj(L, &v, TM_GC);
  if (tm != NULL && ttisfunction(tm)) {  /* is there a finalizer? */
    int status;
    lu_byte oldah = L->allowhook;
    int running  = g->gcrunning;
    L->allowhook = 0;  /* stop debug hooks during GC metamethod */
    g->gcrunning = 0;  /* avoid GC steps */
    setobj2s(L, L->top, tm);  /* push finalizer... */
    setobj2s(L, L->top + 1, &v);  /* ... and its argument */
    L->top += 2;  /* and (next line) call the finalizer */
    status = luaD_pcall(L, dothecall, NULL, savestack(L, L->top - 2), 0);
    L->allowhook = oldah;  /* restore hooks */
    g->gcrunning = running;  /* restore state */
    if (status != LUA_OK && propagateerrors) {  /* error while running __gc? */
      if (status == LUA_ERRRUN) {  /* is there an error object? */
        const char *msg = (ttisstring(L->top - 1))
                            ? svalue(L->top - 1)
                            : "no message";
        luaO_pushfstring(L, "error in __gc metamethod (%s)", msg);
        status = LUA_ERRGCMM;  /* error in __gc metamethod */
      }
      luaD_throw(L, status);  /* re-throw error */
    }
  }
}