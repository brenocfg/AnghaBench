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
 scalar_t__ LUA_OK ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int collectargs (char**,int*) ; 
 int /*<<< orphan*/  createargtable (int /*<<< orphan*/ *,char**,int,int) ; 
 int /*<<< orphan*/  doREPL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ handle_luainit (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_script (int /*<<< orphan*/ *,char**) ; 
 int has_E ; 
 int has_e ; 
 int has_error ; 
 int has_i ; 
 int has_v ; 
 int /*<<< orphan*/  luaL_checkversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lua_stdin_is_tty () ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 int /*<<< orphan*/  print_version () ; 
 char* progname ; 
 int /*<<< orphan*/  runargs (int /*<<< orphan*/ *,char**,int) ; 

__attribute__((used)) static int pmain (lua_State *L) {
  int argc = (int)lua_tointeger(L, 1);
  char **argv = (char **)lua_touserdata(L, 2);
  int script;
  int args = collectargs(argv, &script);
  luaL_checkversion(L);  /* check that interpreter has correct version */
  if (argv[0] && argv[0][0]) progname = argv[0];
  if (args == has_error) {  /* bad arg? */
    print_usage(argv[script]);  /* 'script' has index of bad arg. */
    return 0;
  }
  if (args & has_v)  /* option '-v'? */
    print_version();
  if (args & has_E) {  /* option '-E'? */
    lua_pushboolean(L, 1);  /* signal for libraries to ignore env. vars. */
    lua_setfield(L, LUA_REGISTRYINDEX, "LUA_NOENV");
  }
  luaL_openlibs(L);  /* open standard libraries */
  createargtable(L, argv, argc, script);  /* create table 'arg' */
  if (!(args & has_E)) {  /* no option '-E'? */
    if (handle_luainit(L) != LUA_OK)  /* run LUA_INIT */
      return 0;  /* error running LUA_INIT */
  }
  if (!runargs(L, argv, script))  /* execute arguments -e and -l */
    return 0;  /* something failed */
  if (script < argc &&  /* execute main script (if there is one) */
      handle_script(L, argv + script) != LUA_OK)
    return 0;
  if (args & has_i)  /* -i option? */
    doREPL(L);  /* do read-eval-print loop */
  else if (script == argc && !(args & (has_e | has_v))) {  /* no arguments? */
    if (lua_stdin_is_tty()) {  /* running in interactive mode? */
      print_version();
      doREPL(L);  /* do read-eval-print loop */
    }
    else dofile(L, NULL);  /* executes stdin as a file */
  }
  lua_pushboolean(L, 1);  /* signal no errors */
  return 1;
}