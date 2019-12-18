#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  lua_CFunction ;
struct TYPE_8__ {int /*<<< orphan*/  env; } ;
struct TYPE_10__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 TYPE_7__* funcV (scalar_t__) ; 
 int /*<<< orphan*/  luaL_findtable (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (TYPE_2__*,int,char const*) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lj_lib_prereg(lua_State *L, const char *name, lua_CFunction f, GCtab *env)
{
  luaL_findtable(L, LUA_REGISTRYINDEX, "_PRELOAD", 4);
  lua_pushcfunction(L, f);
  /* NOBARRIER: The function is new (marked white). */
  setgcref(funcV(L->top-1)->c.env, obj2gco(env));
  lua_setfield(L, -2, name);
  L->top--;
}