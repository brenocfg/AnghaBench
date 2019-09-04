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
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ ** newfile (int /*<<< orphan*/ *) ; 
 int pushresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int io_open (lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  const char *mode = luaL_optstring(L, 2, "r");
  FILE **pf = newfile(L);
  *pf = fopen(filename, mode);
  return (*pf == NULL) ? pushresult(L, 0, filename) : 1;
}