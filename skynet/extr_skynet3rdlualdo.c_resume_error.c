#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int LUA_ERRRUN ; 
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  luaS_new (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  lua_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resume_error (lua_State *L, const char *msg, int narg) {
  L->top -= narg;  /* remove args from the stack */
  setsvalue2s(L, L->top, luaS_new(L, msg));  /* push error message */
  api_incr_top(L);
  lua_unlock(L);
  return LUA_ERRRUN;
}