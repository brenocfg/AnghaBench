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
struct Smain {char** argv; int status; int argc; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int FLAGS_EXEC ; 
 int FLAGS_INTERACTIVE ; 
 int FLAGS_NOENV ; 
 int FLAGS_VERSION ; 
 int /*<<< orphan*/  LUAJIT_VERSION_SYM () ; 
 int /*<<< orphan*/  LUA_GCRESTART ; 
 int /*<<< orphan*/  LUA_GCSTOP ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int collectargs (char**,int*) ; 
 int /*<<< orphan*/  dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dotty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * globalL ; 
 int handle_luainit (int /*<<< orphan*/ *) ; 
 int handle_script (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lua_stdin_is_tty () ; 
 int /*<<< orphan*/  print_jit_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  print_version () ; 
 char* progname ; 
 int runargs (int /*<<< orphan*/ *,char**,int) ; 
 struct Smain smain ; 

__attribute__((used)) static int pmain(lua_State *L)
{
  struct Smain *s = &smain;
  char **argv = s->argv;
  int script;
  int flags = 0;
  globalL = L;
  if (argv[0] && argv[0][0]) progname = argv[0];
  LUAJIT_VERSION_SYM();  /* linker-enforced version check */
  script = collectargs(argv, &flags);
  if (script < 0) {  /* invalid args? */
    print_usage();
    s->status = 1;
    return 0;
  }
  if ((flags & FLAGS_NOENV)) {
    lua_pushboolean(L, 1);
    lua_setfield(L, LUA_REGISTRYINDEX, "LUA_NOENV");
  }
  lua_gc(L, LUA_GCSTOP, 0);  /* stop collector during initialization */
  luaL_openlibs(L);  /* open libraries */
  lua_gc(L, LUA_GCRESTART, -1);
  if (!(flags & FLAGS_NOENV)) {
    s->status = handle_luainit(L);
    if (s->status != 0) return 0;
  }
  if ((flags & FLAGS_VERSION)) print_version();
  s->status = runargs(L, argv, (script > 0) ? script : s->argc);
  if (s->status != 0) return 0;
  if (script) {
    s->status = handle_script(L, argv, script);
    if (s->status != 0) return 0;
  }
  if ((flags & FLAGS_INTERACTIVE)) {
    print_jit_status(L);
    dotty(L);
  } else if (script == 0 && !(flags & (FLAGS_EXEC|FLAGS_VERSION))) {
    if (lua_stdin_is_tty()) {
      print_version();
      print_jit_status(L);
      dotty(L);
    } else {
      dofile(L, NULL);  /* executes stdin as a file */
    }
  }
  return 0;
}