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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int os_exit (lua_State *L) {
  int status;
  if (lua_isboolean(L, 1))
    status = (lua_toboolean(L, 1) ? EXIT_SUCCESS : EXIT_FAILURE);
  else
    status = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
  if (lua_toboolean(L, 2))
    lua_close(L);
  if (L) exit(status);  /* 'if' to avoid warnings for unreachable 'return' */
  return 0;
}