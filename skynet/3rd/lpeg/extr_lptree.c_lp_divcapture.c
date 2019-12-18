#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int key; int /*<<< orphan*/  cap; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  Cfunction ; 
 int /*<<< orphan*/  Cnum ; 
 int /*<<< orphan*/  Cquery ; 
 int /*<<< orphan*/  Cstring ; 
#define  LUA_TFUNCTION 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int SHRT_MAX ; 
 int /*<<< orphan*/  TCapture ; 
 int capture_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newroot1sib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp_divcapture (lua_State *L) {
  switch (lua_type(L, 2)) {
    case LUA_TFUNCTION: return capture_aux(L, Cfunction, 2);
    case LUA_TTABLE: return capture_aux(L, Cquery, 2);
    case LUA_TSTRING: return capture_aux(L, Cstring, 2);
    case LUA_TNUMBER: {
      int n = lua_tointeger(L, 2);
      TTree *tree = newroot1sib(L, TCapture);
      luaL_argcheck(L, 0 <= n && n <= SHRT_MAX, 1, "invalid number");
      tree->cap = Cnum;
      tree->key = n;
      return 1;
    }
    default: return luaL_argerror(L, 2, "invalid replacement value");
  }
}