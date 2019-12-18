#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int LJ_52 ; 
 int /*<<< orphan*/  dooptions (TYPE_1__*,int) ; 
 char* luaL_checkstring (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaL_pushmodule (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  lua_getfield (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  lua_isnil (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_pushvalue (TYPE_1__*,int) ; 
 int /*<<< orphan*/  modinit (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  setfenv (TYPE_1__*) ; 

__attribute__((used)) static int lj_cf_package_module(lua_State *L)
{
  const char *modname = luaL_checkstring(L, 1);
  int lastarg = (int)(L->top - L->base);
  luaL_pushmodule(L, modname, 1);
  lua_getfield(L, -1, "_NAME");
  if (!lua_isnil(L, -1)) {  /* Module already initialized? */
    lua_pop(L, 1);
  } else {
    lua_pop(L, 1);
    modinit(L, modname);
  }
  lua_pushvalue(L, -1);
  setfenv(L);
  dooptions(L, lastarg);
  return LJ_52;
}