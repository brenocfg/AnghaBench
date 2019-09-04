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
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 char const* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 

__attribute__((used)) static const char *generic_reader (lua_State *L, void *ud, size_t *size) {
  (void)ud;  /* to avoid warnings */
  luaL_checkstack(L, 2, "too many nested functions");
  lua_pushvalue(L, 1);  /* get function */
  lua_call(L, 0, 1);  /* call it */
  if (lua_isnil(L, -1)) {
    *size = 0;
    return NULL;
  }
  else if (lua_isstring(L, -1)) {
    lua_replace(L, 3);  /* save string in a reserved stack slot */
    return lua_tolstring(L, 3, size);
  }
  else luaL_error(L, "reader function must return a string");
  return NULL;  /* to avoid warnings */
}