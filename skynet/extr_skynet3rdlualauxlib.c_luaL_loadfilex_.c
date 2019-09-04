#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {char* buff; int /*<<< orphan*/ * f; int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ LoadF ;

/* Variables and functions */
 int EOF ; 
 int* LUA_SIGNATURE ; 
 int errfile (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * freopen (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getF ; 
 int /*<<< orphan*/  luaS_expandshr (int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ skipcomment (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * stdin ; 

__attribute__((used)) static int luaL_loadfilex_ (lua_State *L, const char *filename,
                                             const char *mode) {
  LoadF lf;
  int status, readstatus;
  int c;
  int fnameindex = lua_gettop(L) + 1;  /* index of filename on the stack */
  if (filename == NULL) {
    lua_pushliteral(L, "=stdin");
    lf.f = stdin;
  }
  else {
    lua_pushfstring(L, "@%s", filename);
    lf.f = fopen(filename, "r");
    if (lf.f == NULL) return errfile(L, "open", fnameindex);
  }
  if (skipcomment(&lf, &c))  /* read initial portion */
    lf.buff[lf.n++] = '\n';  /* add line to correct line numbers */
  if (c == LUA_SIGNATURE[0] && filename) {  /* binary file? */
    lf.f = freopen(filename, "rb", lf.f);  /* reopen in binary mode */
    if (lf.f == NULL) return errfile(L, "reopen", fnameindex);
    skipcomment(&lf, &c);  /* re-read initial portion */
  }
  if (c != EOF)
    lf.buff[lf.n++] = c;  /* 'c' is the first character of the stream */
  luaS_expandshr(4096);
  status = lua_load(L, getF, &lf, lua_tostring(L, -1), mode);
  luaS_expandshr(-4096);
  readstatus = ferror(lf.f);
  if (filename) fclose(lf.f);  /* close file (even in case of errors) */
  if (readstatus) {
    lua_settop(L, fnameindex);  /* ignore results from 'lua_load' */
    return errfile(L, "read", fnameindex);
  }
  lua_remove(L, fnameindex);
  return status;
}