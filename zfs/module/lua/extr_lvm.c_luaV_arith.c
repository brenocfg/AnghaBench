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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int TMS ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int LUA_OPADD ; 
 int LUA_OPDIV ; 
 int LUA_OPMOD ; 
 int TM_ADD ; 
 int /*<<< orphan*/  call_binTM (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaG_aritherror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaO_arith (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaV_div (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaV_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaV_tonumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setnvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luaV_arith (lua_State *L, StkId ra, const TValue *rb,
                 const TValue *rc, TMS op) {
  TValue tempb, tempc;
  const TValue *b, *c;
  if ((b = luaV_tonumber(rb, &tempb)) != NULL &&
      (c = luaV_tonumber(rc, &tempc)) != NULL) {
    /*
     * Patched: if dividing or modding, use patched functions from 5.3
     */
    lua_Number res;
    int lop = op - TM_ADD + LUA_OPADD;
    if (lop == LUA_OPDIV) {
      res = luaV_div(L, nvalue(b), nvalue(c));
    } else if (lop == LUA_OPMOD) {
      res = luaV_mod(L, nvalue(b), nvalue(c));
    } else {
      res = luaO_arith(op - TM_ADD + LUA_OPADD, nvalue(b), nvalue(c));
    }
    setnvalue(ra, res);
  }
  else if (!call_binTM(L, rb, rc, ra, op))
    luaG_aritherror(L, rb, rc);
}