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
typedef  int /*<<< orphan*/  lua_CFunction ;

/* Variables and functions */
 char const* luaT_newlocalmetatable (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char* luaT_newmetatable(lua_State *L, const char *tname, const char *parent_tname,
                              lua_CFunction constructor, lua_CFunction destructor, lua_CFunction factory)
{
  return luaT_newlocalmetatable(L, tname, parent_tname,
                                constructor, destructor, factory, 0);
}