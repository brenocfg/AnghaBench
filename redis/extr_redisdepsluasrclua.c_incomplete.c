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
 int LUA_ERRSYNTAX ; 
 int /*<<< orphan*/  LUA_QL (char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 char const* strstr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int incomplete (lua_State *L, int status) {
  if (status == LUA_ERRSYNTAX) {
    size_t lmsg;
    const char *msg = lua_tolstring(L, -1, &lmsg);
    const char *tp = msg + lmsg - (sizeof(LUA_QL("<eof>")) - 1);
    if (strstr(msg, LUA_QL("<eof>")) == tp) {
      lua_pop(L, 1);
      return 1;
    }
  }
  return 0;  /* else... */
}