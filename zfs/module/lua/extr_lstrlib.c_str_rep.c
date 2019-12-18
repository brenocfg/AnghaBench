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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int MAXSIZE ; 
 char* luaL_buffinitsize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 char* luaL_optlstring (int /*<<< orphan*/ *,int,char*,size_t*) ; 
 int /*<<< orphan*/  luaL_pushresultsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int str_rep (lua_State *L) {
  size_t l, lsep;
  const char *s = luaL_checklstring(L, 1, &l);
  int n = luaL_checkint(L, 2);
  const char *sep = luaL_optlstring(L, 3, "", &lsep);
  if (n <= 0) lua_pushliteral(L, "");
  else if (l + lsep < l || l + lsep >= MAXSIZE / n)  /* may overflow? */
    return luaL_error(L, "resulting string too large");
  else {
    size_t totallen = n * l + (n - 1) * lsep;
    luaL_Buffer b;
    char *p = luaL_buffinitsize(L, &b, totallen);
    while (n-- > 1) {  /* first n-1 copies (followed by separator) */
      memcpy(p, s, l * sizeof(char)); p += l;
      if (lsep > 0) {  /* avoid empty 'memcpy' (may be expensive) */
        memcpy(p, sep, lsep * sizeof(char)); p += lsep;
      }
    }
    memcpy(p, s, l * sizeof(char));  /* last copy (not followed by separator) */
    luaL_pushresultsize(&b, totallen);
  }
  return 1;
}