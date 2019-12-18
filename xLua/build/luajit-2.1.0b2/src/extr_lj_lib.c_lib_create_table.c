#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_BADMODN ; 
 int /*<<< orphan*/  LUA_GLOBALSINDEX ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lj_err_callerv (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * luaL_findtable (TYPE_1__*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  lua_createtable (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_getfield (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  lua_setfield (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  settabV (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tabV (scalar_t__) ; 
 int /*<<< orphan*/  tvistab (scalar_t__) ; 

__attribute__((used)) static GCtab *lib_create_table(lua_State *L, const char *libname, int hsize)
{
  if (libname) {
    luaL_findtable(L, LUA_REGISTRYINDEX, "_LOADED", 16);
    lua_getfield(L, -1, libname);
    if (!tvistab(L->top-1)) {
      L->top--;
      if (luaL_findtable(L, LUA_GLOBALSINDEX, libname, hsize) != NULL)
	lj_err_callerv(L, LJ_ERR_BADMODN, libname);
      settabV(L, L->top, tabV(L->top-1));
      L->top++;
      lua_setfield(L, -3, libname);  /* _LOADED[libname] = new table */
    }
    L->top--;
    settabV(L, L->top-1, tabV(L->top));
  } else {
    lua_createtable(L, 0, hsize);
  }
  return tabV(L->top-1);
}