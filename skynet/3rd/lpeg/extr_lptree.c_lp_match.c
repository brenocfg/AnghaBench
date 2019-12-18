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
struct TYPE_4__ {int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ Pattern ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  Capture ;

/* Variables and functions */
 int INITCAPSIZE ; 
 int /*<<< orphan*/  SUBJIDX ; 
 int getcaptures (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 TYPE_1__* getpatt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpattern (int /*<<< orphan*/ *,int) ; 
 size_t initposition (int /*<<< orphan*/ *,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* match (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * prepcompile (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int lp_match (lua_State *L) {
  Capture capture[INITCAPSIZE];
  const char *r;
  size_t l;
  Pattern *p = (getpatt(L, 1, NULL), getpattern(L, 1));
  Instruction *code = (p->code != NULL) ? p->code : prepcompile(L, p, 1);
  const char *s = luaL_checklstring(L, SUBJIDX, &l);
  size_t i = initposition(L, l);
  int ptop = lua_gettop(L);
  lua_pushnil(L);  /* initialize subscache */
  lua_pushlightuserdata(L, capture);  /* initialize caplistidx */
  lua_getuservalue(L, 1);  /* initialize penvidx */
  r = match(L, s, s + i, s + l, code, capture, ptop);
  if (r == NULL) {
    lua_pushnil(L);
    return 1;
  }
  return getcaptures(L, s, r, ptop);
}