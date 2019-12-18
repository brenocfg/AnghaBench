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
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 int LUA_IDSIZE ; 
 int /*<<< orphan*/  getstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaO_chunkid (char*,int /*<<< orphan*/ ,int) ; 
 char const* luaO_pushfstring (int /*<<< orphan*/ *,char*,char*,int,char const*) ; 

const char *luaG_addinfo (lua_State *L, const char *msg, TString *src,
                                        int line) {
  char buff[LUA_IDSIZE];
  if (src)
    luaO_chunkid(buff, getstr(src), LUA_IDSIZE);
  else {  /* no source available; use "?" instead */
    buff[0] = '?'; buff[1] = '\0';
  }
  return luaO_pushfstring(L, "%s:%d: %s", buff, line, msg);
}