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

/* Variables and functions */
#define  LUA_OPADD 135 
#define  LUA_OPDIV 134 
#define  LUA_OPIDIV 133 
#define  LUA_OPMOD 132 
#define  LUA_OPMUL 131 
#define  LUA_OPPOW 130 
#define  LUA_OPSUB 129 
#define  LUA_OPUNM 128 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numadd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numdiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numidiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_nummod (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_nummul (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numpow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numsub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numunm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static lua_Number numarith (lua_State *L, int op, lua_Number v1,
                                                  lua_Number v2) {
  switch (op) {
    case LUA_OPADD: return luai_numadd(L, v1, v2);
    case LUA_OPSUB: return luai_numsub(L, v1, v2);
    case LUA_OPMUL: return luai_nummul(L, v1, v2);
    case LUA_OPDIV: return luai_numdiv(L, v1, v2);
    case LUA_OPPOW: return luai_numpow(L, v1, v2);
    case LUA_OPIDIV: return luai_numidiv(L, v1, v2);
    case LUA_OPUNM: return luai_numunm(L, v1);
    case LUA_OPMOD: {
      lua_Number m;
      luai_nummod(L, v1, v2, m);
      return m;
    }
    default: lua_assert(0); return 0;
  }
}