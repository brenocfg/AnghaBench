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
typedef  scalar_t__ lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  l_rand () ; 
 int /*<<< orphan*/  l_srand (unsigned int) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int math_randomseed (lua_State *L) {
  l_srand((unsigned int)(lua_Integer)luaL_checknumber(L, 1));
  (void)l_rand(); /* discard first value to avoid undesirable correlations */
  return 0;
}