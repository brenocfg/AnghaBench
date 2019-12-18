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
 int load_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_loadbuffer (int /*<<< orphan*/ *,char const*,size_t,char const*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static int luaB_loadstring (lua_State *L) {
  size_t l;
  const char *s = luaL_checklstring(L, 1, &l);
  const char *chunkname = luaL_optstring(L, 2, s);
  return load_aux(L, luaL_loadbuffer(L, s, l, chunkname));
}