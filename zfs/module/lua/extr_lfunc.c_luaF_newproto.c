#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/ * source; scalar_t__ lastlinedefined; scalar_t__ linedefined; scalar_t__ sizelocvars; int /*<<< orphan*/ * locvars; scalar_t__ maxstacksize; scalar_t__ is_vararg; scalar_t__ numparams; scalar_t__ sizeupvalues; int /*<<< orphan*/ * upvalues; scalar_t__ sizelineinfo; int /*<<< orphan*/ * lineinfo; scalar_t__ sizecode; int /*<<< orphan*/ * cache; int /*<<< orphan*/ * code; scalar_t__ sizep; int /*<<< orphan*/ * p; scalar_t__ sizek; int /*<<< orphan*/ * k; } ;
struct TYPE_5__ {TYPE_1__ p; } ;
typedef  TYPE_1__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TPROTO ; 
 TYPE_3__* luaC_newobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Proto *luaF_newproto (lua_State *L) {
  Proto *f = &luaC_newobj(L, LUA_TPROTO, sizeof(Proto), NULL, 0)->p;
  f->k = NULL;
  f->sizek = 0;
  f->p = NULL;
  f->sizep = 0;
  f->code = NULL;
  f->cache = NULL;
  f->sizecode = 0;
  f->lineinfo = NULL;
  f->sizelineinfo = 0;
  f->upvalues = NULL;
  f->sizeupvalues = 0;
  f->numparams = 0;
  f->is_vararg = 0;
  f->maxstacksize = 0;
  f->locvars = NULL;
  f->sizelocvars = 0;
  f->linedefined = 0;
  f->lastlinedefined = 0;
  f->source = NULL;
  return f;
}