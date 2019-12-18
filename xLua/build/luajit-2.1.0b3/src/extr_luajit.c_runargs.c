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
 int LUA_OK ; 
 int dobytecode (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  dojitcmd (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dojitopt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dolibrary (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dostring (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static int runargs(lua_State *L, char **argv, int argn)
{
  int i;
  for (i = 1; i < argn; i++) {
    if (argv[i] == NULL) continue;
    lua_assert(argv[i][0] == '-');
    switch (argv[i][1]) {
    case 'e': {
      const char *chunk = argv[i] + 2;
      if (*chunk == '\0') chunk = argv[++i];
      lua_assert(chunk != NULL);
      if (dostring(L, chunk, "=(command line)") != 0)
	return 1;
      break;
      }
    case 'l': {
      const char *filename = argv[i] + 2;
      if (*filename == '\0') filename = argv[++i];
      lua_assert(filename != NULL);
      if (dolibrary(L, filename))
	return 1;
      break;
      }
    case 'j': {  /* LuaJIT extension. */
      const char *cmd = argv[i] + 2;
      if (*cmd == '\0') cmd = argv[++i];
      lua_assert(cmd != NULL);
      if (dojitcmd(L, cmd))
	return 1;
      break;
      }
    case 'O':  /* LuaJIT extension. */
      if (dojitopt(L, argv[i] + 2))
	return 1;
      break;
    case 'b':  /* LuaJIT extension. */
      return dobytecode(L, argv+i);
    default: break;
    }
  }
  return LUA_OK;
}