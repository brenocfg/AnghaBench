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
typedef  int /*<<< orphan*/  l_noret ;
struct TYPE_4__ {int /*<<< orphan*/  L; int /*<<< orphan*/  linenumber; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_ERRSYNTAX ; 
 int LUA_IDSIZE ; 
 int /*<<< orphan*/  getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaD_throw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaO_chunkid (char*,int /*<<< orphan*/ ,int) ; 
 char* luaO_pushfstring (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  txtToken (TYPE_1__*,int) ; 

__attribute__((used)) static l_noret lexerror (LexState *ls, const char *msg, int token) {
  char buff[LUA_IDSIZE];
  luaO_chunkid(buff, getstr(ls->source), LUA_IDSIZE);
  msg = luaO_pushfstring(ls->L, "%s:%d: %s", buff, ls->linenumber, msg);
  if (token)
    luaO_pushfstring(ls->L, "%s near %s", msg, txtToken(ls, token));
  luaD_throw(ls->L, LUA_ERRSYNTAX);
}