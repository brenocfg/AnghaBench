#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {size_t lnglen; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TLNGSTR ; 
 int /*<<< orphan*/  STRSEED ; 
 TYPE_2__* createstrobj (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TString *luaS_createlngstrobj (lua_State *L, size_t l) {
  TString *ts = createstrobj(L, l, LUA_TLNGSTR, STRSEED);
  ts->u.lnglen = l;
  return ts;
}