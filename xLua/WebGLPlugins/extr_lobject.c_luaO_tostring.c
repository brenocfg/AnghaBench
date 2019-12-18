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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int MAXNUMBER2STR ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_newlstr (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 char lua_getlocaledecpoint () ; 
 size_t lua_integer2str (char*,int,int /*<<< orphan*/ ) ; 
 size_t lua_number2str (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsvalue2s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strspn (char*,char*) ; 
 scalar_t__ ttisinteger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttisnumber (int /*<<< orphan*/ ) ; 

void luaO_tostring (lua_State *L, StkId obj) {
  char buff[MAXNUMBER2STR];
  size_t len;
  lua_assert(ttisnumber(obj));
  if (ttisinteger(obj))
    len = lua_integer2str(buff, sizeof(buff), ivalue(obj));
  else {
    len = lua_number2str(buff, sizeof(buff), fltvalue(obj));
#if !defined(LUA_COMPAT_FLOATSTRING)
    if (buff[strspn(buff, "-0123456789")] == '\0') {  /* looks like an int? */
      buff[len++] = lua_getlocaledecpoint();
      buff[len++] = '0';  /* adds '.0' to result */
    }
#endif
  }
  setsvalue2s(L, obj, luaS_newlstr(L, buff, len));
}