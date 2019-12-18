#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {size_t len; int /*<<< orphan*/ * env; int /*<<< orphan*/ * metatable; } ;
struct TYPE_6__ {TYPE_1__ uv; } ;
typedef  TYPE_2__ Udata ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_7__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TUSERDATA ; 
 int MAX_SIZET ; 
 TYPE_4__* luaC_newobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_toobig (int /*<<< orphan*/ *) ; 

Udata *luaS_newudata (lua_State *L, size_t s, Table *e) {
  Udata *u;
  if (s > MAX_SIZET - sizeof(Udata))
    luaM_toobig(L);
  u = &luaC_newobj(L, LUA_TUSERDATA, sizeof(Udata) + s, NULL, 0)->u;
  u->uv.len = s;
  u->uv.metatable = NULL;
  u->uv.env = e;
  return u;
}