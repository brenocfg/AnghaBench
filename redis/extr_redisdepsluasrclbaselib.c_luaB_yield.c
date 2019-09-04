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
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int luaB_yield (lua_State *L) {
  return lua_yield(L, lua_gettop(L));
}