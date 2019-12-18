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
typedef  int /*<<< orphan*/ * lua_CFunction ;

/* Variables and functions */
 int ERRFUNC ; 
 int ERRLIB ; 
 void* ll_load (int /*<<< orphan*/ *,char const*) ; 
 void** ll_register (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * ll_sym (int /*<<< orphan*/ *,void*,char const*) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ll_loadfunc (lua_State *L, const char *path, const char *sym) {
  void **reg = ll_register(L, path);
  if (*reg == NULL) *reg = ll_load(L, path);
  if (*reg == NULL)
    return ERRLIB;  /* unable to load library */
  else {
    lua_CFunction f = ll_sym(L, *reg, sym);
    if (f == NULL)
      return ERRFUNC;  /* unable to find function */
    lua_pushcfunction(L, f);
    return 0;  /* return function */
  }
}