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
#define  TM_BAND 134 
#define  TM_BNOT 133 
#define  TM_BOR 132 
#define  TM_BXOR 131 
#define  TM_CONCAT 130 
#define  TM_SHL 129 
#define  TM_SHR 128 
 int /*<<< orphan*/  luaG_concaterror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaG_opinterror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  luaG_tointerror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaT_callbinTM (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tonumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void luaT_trybinTM (lua_State *L, const TValue *p1, const TValue *p2,
                    StkId res, TMS event) {
  if (!luaT_callbinTM(L, p1, p2, res, event)) {
    switch (event) {
      case TM_CONCAT:
        luaG_concaterror(L, p1, p2);
      /* call never returns, but to avoid warnings: *//* FALLTHROUGH */
      case TM_BAND: case TM_BOR: case TM_BXOR:
      case TM_SHL: case TM_SHR: case TM_BNOT: {
        lua_Number dummy;
        if (tonumber(p1, &dummy) && tonumber(p2, &dummy))
          luaG_tointerror(L, p1, p2);
        else
          luaG_opinterror(L, p1, p2, "perform bitwise operation on");
      }
      /* calls never return, but to avoid warnings: *//* FALLTHROUGH */
      default:
        luaG_opinterror(L, p1, p2, "perform arithmetic on");
    }
  }
}