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
struct TYPE_6__ {int hookmask; scalar_t__ top; int /*<<< orphan*/  savedpc; int /*<<< orphan*/  base; int /*<<< orphan*/  ci; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_7__ {scalar_t__ func; int nresults; int /*<<< orphan*/  savedpc; int /*<<< orphan*/  base; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_2__ CallInfo ;

/* Variables and functions */
 int LUA_MASKRET ; 
 int LUA_MULTRET ; 
 scalar_t__ callrethooks (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int luaD_poscall (lua_State *L, StkId firstResult) {
  StkId res;
  int wanted, i;
  CallInfo *ci;
  if (L->hookmask & LUA_MASKRET)
    firstResult = callrethooks(L, firstResult);
  ci = L->ci--;
  res = ci->func;  /* res == final position of 1st result */
  wanted = ci->nresults;
  L->base = (ci - 1)->base;  /* restore base */
  L->savedpc = (ci - 1)->savedpc;  /* restore savedpc */
  /* move results to correct place */
  for (i = wanted; i != 0 && firstResult < L->top; i--)
    setobjs2s(L, res++, firstResult++);
  while (i-- > 0)
    setnilvalue(res++);
  L->top = res;
  return (wanted - LUA_MULTRET);  /* 0 iff wanted == LUA_MULTRET */
}