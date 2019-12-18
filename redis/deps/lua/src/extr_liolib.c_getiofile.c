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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_ENVIRONINDEX ; 
 int /*<<< orphan*/ * fnames ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static FILE *getiofile (lua_State *L, int findex) {
  FILE *f;
  lua_rawgeti(L, LUA_ENVIRONINDEX, findex);
  f = *(FILE **)lua_touserdata(L, -1);
  if (f == NULL)
    luaL_error(L, "standard %s file is closed", fnames[findex - 1]);
  return f;
}