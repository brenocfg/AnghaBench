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
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  md5 (char const*,size_t,char*) ; 

__attribute__((used)) static int lmd5 (lua_State *L) {
  char buff[16];
  size_t l;
  const char *message = luaL_checklstring(L, 1, &l);
  md5(message, l, buff);
  lua_pushlstring(L, buff, 16L);
  return 1;
}