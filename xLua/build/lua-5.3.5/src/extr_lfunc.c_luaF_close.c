#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* openupval; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_12__ {TYPE_4__* next; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; TYPE_1__ open; } ;
struct TYPE_15__ {scalar_t__ v; scalar_t__ refcount; TYPE_2__ u; } ;
typedef  TYPE_4__ UpVal ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  luaC_upvalbarrier (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  luaM_free (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  upisopen (TYPE_4__*) ; 

void luaF_close (lua_State *L, StkId level) {
  UpVal *uv;
  while (L->openupval != NULL && (uv = L->openupval)->v >= level) {
    lua_assert(upisopen(uv));
    L->openupval = uv->u.open.next;  /* remove from 'open' list */
    if (uv->refcount == 0)  /* no references? */
      luaM_free(L, uv);  /* free upvalue */
    else {
      setobj(L, &uv->u.value, uv->v);  /* move value to upvalue slot */
      uv->v = &uv->u.value;  /* now current value lives here */
      luaC_upvalbarrier(L, uv);
    }
  }
}