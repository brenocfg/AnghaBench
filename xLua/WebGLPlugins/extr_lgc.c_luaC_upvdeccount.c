#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {scalar_t__ refcount; } ;
typedef  TYPE_1__ UpVal ;

/* Variables and functions */
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  upisopen (TYPE_1__*) ; 

void luaC_upvdeccount (lua_State *L, UpVal *uv) {
  lua_assert(uv->refcount > 0);
  uv->refcount--;
  if (uv->refcount == 0 && !upisopen(uv))
    luaM_free(L, uv);
}