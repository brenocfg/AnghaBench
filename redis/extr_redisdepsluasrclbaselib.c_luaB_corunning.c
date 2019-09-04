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

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pushthread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int luaB_corunning (lua_State *L) {
  if (lua_pushthread(L))
    lua_pushnil(L);  /* main thread is not a coroutine */
  return 1;
}