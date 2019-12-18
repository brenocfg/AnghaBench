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
 int /*<<< orphan*/  IO_INPUT ; 
 int /*<<< orphan*/  LUA_ENVIRONINDEX ; 
 int /*<<< orphan*/  aux_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int f_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileerror (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** newfile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_lines (lua_State *L) {
  if (lua_isnoneornil(L, 1)) {  /* no arguments? */
    /* will iterate over default input */
    lua_rawgeti(L, LUA_ENVIRONINDEX, IO_INPUT);
    return f_lines(L);
  }
  else {
    const char *filename = luaL_checkstring(L, 1);
    FILE **pf = newfile(L);
    *pf = fopen(filename, "r");
    if (*pf == NULL)
      fileerror(L, 1, filename);
    aux_lines(L, lua_gettop(L), 1);
    return 1;
  }
}