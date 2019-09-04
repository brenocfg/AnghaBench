#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * openupval; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_14__ {int /*<<< orphan*/  value; } ;
struct TYPE_16__ {scalar_t__ v; TYPE_1__ u; int /*<<< orphan*/ * next; } ;
typedef  TYPE_3__ UpVal ;
typedef  scalar_t__ StkId ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/ * G (TYPE_2__*) ; 
 int /*<<< orphan*/  isblack (int /*<<< orphan*/ *) ; 
 scalar_t__ isdead (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaC_linkupval (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaF_freeupval (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_3__* ngcotouv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obj2gco (TYPE_3__*) ; 
 int /*<<< orphan*/  setobj (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlinkupval (TYPE_3__*) ; 

void luaF_close (lua_State *L, StkId level) {
  UpVal *uv;
  global_State *g = G(L);
  while (L->openupval != NULL && (uv = ngcotouv(L->openupval))->v >= level) {
    GCObject *o = obj2gco(uv);
    lua_assert(!isblack(o) && uv->v != &uv->u.value);
    L->openupval = uv->next;  /* remove from `open' list */
    if (isdead(g, o))
      luaF_freeupval(L, uv);  /* free upvalue */
    else {
      unlinkupval(uv);
      setobj(L, &uv->u.value, uv->v);
      uv->v = &uv->u.value;  /* now current value lives here */
      luaC_linkupval(L, uv);  /* link upvalue into `gcroot' list */
    }
  }
}