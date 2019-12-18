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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_pclose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pushresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** tofilep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_pclose (lua_State *L) {
#if defined(WINAPI_FAMILY_PARTITION)
  return luaL_error(L, "unsupport api in uwp platform");
#else
  FILE **p = tofilep(L);
  int ok = lua_pclose(L, *p);
  *p = NULL;
  return pushresult(L, ok, NULL);
#endif
}