#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ci; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  callstatus; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  CIST_LEQ ; 
 int LEnum (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TM_LE ; 
 int /*<<< orphan*/  TM_LT ; 
 scalar_t__ l_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaG_ordererror (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int luaT_callorderTM (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 

int luaV_lessequal (lua_State *L, const TValue *l, const TValue *r) {
  int res;
  if (ttisnumber(l) && ttisnumber(r))  /* both operands are numbers? */
    return LEnum(l, r);
  else if (ttisstring(l) && ttisstring(r))  /* both are strings? */
    return l_strcmp(tsvalue(l), tsvalue(r)) <= 0;
  else if ((res = luaT_callorderTM(L, l, r, TM_LE)) >= 0)  /* try 'le' */
    return res;
  else {  /* try 'lt': */
    L->ci->callstatus |= CIST_LEQ;  /* mark it is doing 'lt' for 'le' */
    res = luaT_callorderTM(L, r, l, TM_LT);
    L->ci->callstatus ^= CIST_LEQ;  /* clear mark */
    if (res < 0)
      luaG_ordererror(L, l, r);
    return !res;  /* result is negated */
  }
}