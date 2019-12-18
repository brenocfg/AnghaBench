#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  Stack ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  MAXSTACKIDX ; 
 int /*<<< orphan*/ * getstackbase (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stackidx (int) ; 

__attribute__((used)) static Stack *doublestack (lua_State *L, Stack **stacklimit, int ptop) {
  Stack *stack = getstackbase(L, ptop);
  Stack *newstack;
  int n = *stacklimit - stack;  /* current stack size */
  int max, newn;
  lua_getfield(L, LUA_REGISTRYINDEX, MAXSTACKIDX);
  max = lua_tointeger(L, -1);  /* maximum allowed size */
  lua_pop(L, 1);
  if (n >= max)  /* already at maximum size? */
    luaL_error(L, "backtrack stack overflow (current limit is %d)", max);
  newn = 2 * n;  /* new size */
  if (newn > max) newn = max;
  newstack = (Stack *)lua_newuserdata(L, newn * sizeof(Stack));
  memcpy(newstack, stack, n * sizeof(Stack));
  lua_replace(L, stackidx(ptop));
  *stacklimit = newstack + newn;
  return newstack + n;  /* return next position */
}