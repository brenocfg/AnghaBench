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
typedef  scalar_t__ lua_CFunction ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_MAX_BUF ; 
 int PACKAGE_ERR_FUNC ; 
 int PACKAGE_ERR_LIB ; 
 int PACKAGE_ERR_LOAD ; 
 int /*<<< orphan*/  SYMPREFIX_BC ; 
 int /*<<< orphan*/  SYMPREFIX_CF ; 
 char* ll_bcsym (void*,char const*) ; 
 void* ll_load (int /*<<< orphan*/ *,char const*,int) ; 
 void** ll_register (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ ll_sym (int /*<<< orphan*/ *,void*,char const*) ; 
 scalar_t__ luaL_loadbuffer (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,scalar_t__) ; 
 char const* mksymname (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ll_loadfunc(lua_State *L, const char *path, const char *name, int r)
{
  void **reg = ll_register(L, path);
  if (*reg == NULL) *reg = ll_load(L, path, (*name == '*'));
  if (*reg == NULL) {
    return PACKAGE_ERR_LIB;  /* Unable to load library. */
  } else if (*name == '*') {  /* Only load library into global namespace. */
    lua_pushboolean(L, 1);
    return 0;
  } else {
    const char *sym = r ? name : mksymname(L, name, SYMPREFIX_CF);
    lua_CFunction f = ll_sym(L, *reg, sym);
    if (f) {
      lua_pushcfunction(L, f);
      return 0;
    }
    if (!r) {
      const char *bcdata = ll_bcsym(*reg, mksymname(L, name, SYMPREFIX_BC));
      lua_pop(L, 1);
      if (bcdata) {
	if (luaL_loadbuffer(L, bcdata, LJ_MAX_BUF, name) != 0)
	  return PACKAGE_ERR_LOAD;
	return 0;
      }
    }
    return PACKAGE_ERR_FUNC;  /* Unable to find function. */
  }
}