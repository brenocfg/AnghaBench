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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/ * v; } ;
typedef  TYPE_2__ UpVal ;

/* Variables and functions */
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  unlinkupval (TYPE_2__*) ; 

void luaF_freeupval (lua_State *L, UpVal *uv) {
  if (uv->v != &uv->u.value)  /* is it open? */
    unlinkupval(uv);  /* remove from open list */
  luaM_free(L, uv);  /* free upvalue */
}