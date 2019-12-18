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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 char* luaT_typenameid (int /*<<< orphan*/ *,char const*) ; 

const char* luaT_checktypename2id(lua_State *L, const char *tname)
{
  const char* id = luaT_typenameid(L, tname);
  if(!id)
    luaL_error(L, "unknown class <%s>", tname);
  return id;
}