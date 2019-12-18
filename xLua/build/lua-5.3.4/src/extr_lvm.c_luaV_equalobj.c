#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ lua_Integer ;
struct TYPE_9__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_8__ {int /*<<< orphan*/  metatable; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
#define  LUA_TBOOLEAN 137 
#define  LUA_TLCF 136 
#define  LUA_TLIGHTUSERDATA 135 
#define  LUA_TLNGSTR 134 
#define  LUA_TNIL 133 
 scalar_t__ LUA_TNUMBER ; 
#define  LUA_TNUMFLT 132 
#define  LUA_TNUMINT 131 
#define  LUA_TSHRSTR 130 
#define  LUA_TTABLE 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  TM_EQ ; 
 int /*<<< orphan*/  bvalue (int /*<<< orphan*/  const*) ; 
 int eqshrstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fasttm (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/  const*) ; 
 TYPE_5__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  l_isfalse (int /*<<< orphan*/ ) ; 
 int luaS_eqlngstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaT_callTM (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int luai_numeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ tointeger (int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttnov (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 
 TYPE_2__* uvalue (int /*<<< orphan*/  const*) ; 

int luaV_equalobj (lua_State *L, const TValue *t1, const TValue *t2) {
  const TValue *tm;
  if (ttype(t1) != ttype(t2)) {  /* not the same variant? */
    if (ttnov(t1) != ttnov(t2) || ttnov(t1) != LUA_TNUMBER)
      return 0;  /* only numbers can be equal with different variants */
    else {  /* two numbers with different variants */
      lua_Integer i1, i2;  /* compare them as integers */
      return (tointeger(t1, &i1) && tointeger(t2, &i2) && i1 == i2);
    }
  }
  /* values have same type and same variant */
  switch (ttype(t1)) {
    case LUA_TNIL: return 1;
    case LUA_TNUMINT: return (ivalue(t1) == ivalue(t2));
    case LUA_TNUMFLT: return luai_numeq(fltvalue(t1), fltvalue(t2));
    case LUA_TBOOLEAN: return bvalue(t1) == bvalue(t2);  /* true must be 1 !! */
    case LUA_TLIGHTUSERDATA: return pvalue(t1) == pvalue(t2);
    case LUA_TLCF: return fvalue(t1) == fvalue(t2);
    case LUA_TSHRSTR: return eqshrstr(tsvalue(t1), tsvalue(t2));
    case LUA_TLNGSTR: return luaS_eqlngstr(tsvalue(t1), tsvalue(t2));
    case LUA_TUSERDATA: {
      if (uvalue(t1) == uvalue(t2)) return 1;
      else if (L == NULL) return 0;
      tm = fasttm(L, uvalue(t1)->metatable, TM_EQ);
      if (tm == NULL)
        tm = fasttm(L, uvalue(t2)->metatable, TM_EQ);
      break;  /* will try TM */
    }
    case LUA_TTABLE: {
      if (hvalue(t1) == hvalue(t2)) return 1;
      else if (L == NULL) return 0;
      tm = fasttm(L, hvalue(t1)->metatable, TM_EQ);
      if (tm == NULL)
        tm = fasttm(L, hvalue(t2)->metatable, TM_EQ);
      break;  /* will try TM */
    }
    default:
      return gcvalue(t1) == gcvalue(t2);
  }
  if (tm == NULL)  /* no TM? */
    return 0;  /* objects are different */
  luaT_callTM(L, tm, t1, t2, L->top, 1);  /* call TM */
  return !l_isfalse(L->top);
}