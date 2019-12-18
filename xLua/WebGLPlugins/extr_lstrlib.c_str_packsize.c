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
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int KOption ;
typedef  int /*<<< orphan*/  Header ;

/* Variables and functions */
#define  Kstring 129 
#define  Kzstr 128 
 int MAXSIZE ; 
 int getdetails (int /*<<< orphan*/ *,size_t,char const**,int*,int*) ; 
 int /*<<< orphan*/  initheader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int str_packsize (lua_State *L) {
  Header h;
  const char *fmt = luaL_checkstring(L, 1);  /* format string */
  size_t totalsize = 0;  /* accumulate total size of result */
  initheader(L, &h);
  while (*fmt != '\0') {
    int size, ntoalign;
    KOption opt = getdetails(&h, totalsize, &fmt, &size, &ntoalign);
    size += ntoalign;  /* total space used by option */
    luaL_argcheck(L, totalsize <= MAXSIZE - size, 1,
                     "format result too large");
    totalsize += size;
    switch (opt) {
      case Kstring:  /* strings with length count */
      case Kzstr:    /* zero-terminated string */
        luaL_argerror(L, 1, "variable-length format");
        /* call never return, but to avoid warnings: *//* FALLTHROUGH */
      default:  break;
    }
  }
  lua_pushinteger(L, (lua_Integer)totalsize);
  return 1;
}