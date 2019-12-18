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
 void* luaT_toudata (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  luaT_typerror (int /*<<< orphan*/ *,int,char const*) ; 

void *luaT_checkudata(lua_State *L, int ud, const char *tname)
{
  void *p = luaT_toudata(L, ud, tname);
  if(!p)
    luaT_typerror(L, ud, tname);
  return p;
}