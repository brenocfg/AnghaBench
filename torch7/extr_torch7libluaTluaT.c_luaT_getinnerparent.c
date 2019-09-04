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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int strcspn (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void luaT_getinnerparent(lua_State *L, const char *tname)
{
  /* Local variables */
  char term[256];
  char chars[] = {'.', '\0'};
  const char *tname_full = tname; // used for error case

  /* Get outermost table from Lua */
  int n = strcspn(tname, chars);
  strncpy(term, tname, n);
  term[n] = '\0';
  lua_getglobal(L, term);
  tname  += n + 1;

  /* Traverse hierarchy down to last table*/
  n = strcspn(tname, chars);
  while(n < strlen(tname))
  {
    /* Check that current parent is a table (i.e. a module) */
    if(!lua_istable(L, -1)){
      strncpy(term, tname_full, tname - tname_full - 1);
      term[tname - tname_full] = '\0';
      luaL_error(L, "while creating metatable %s: bad argument #1 (%s is an invalid module name)", tname_full, term);
    }
    strncpy(term, tname, n);
    term[n] = '\0';
    lua_getfield(L, -1, term);
    lua_remove(L, -2);
    tname += n + 1;
    n = strcspn(tname, chars); // prepare for next
  }

  /* Check that resulting parent is a table (i.e. a module) */
  if(!lua_istable(L, -1)){
    strncpy(term, tname_full, tname - tname_full - 1);
    term[tname - tname_full] = '\0';
    luaL_error(L, "while creating metatable %s: bad argument #1 (%s is an invalid module name)", tname_full, term);
  }
}