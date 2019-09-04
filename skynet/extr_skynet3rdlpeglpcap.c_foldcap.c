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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int idx; } ;
struct TYPE_6__ {TYPE_4__* cap; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 scalar_t__ isclosecap (TYPE_4__*) ; 
 scalar_t__ isfullcap (int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pushcapture (TYPE_1__*) ; 
 int /*<<< orphan*/  updatecache (TYPE_1__*,int) ; 

__attribute__((used)) static int foldcap (CapState *cs) {
  int n;
  lua_State *L = cs->L;
  int idx = cs->cap->idx;
  if (isfullcap(cs->cap++) ||  /* no nested captures? */
      isclosecap(cs->cap) ||  /* no nested captures (large subject)? */
      (n = pushcapture(cs)) == 0)  /* nested captures with no values? */
    return luaL_error(L, "no initial value for fold capture");
  if (n > 1)
    lua_pop(L, n - 1);  /* leave only one result for accumulator */
  while (!isclosecap(cs->cap)) {
    lua_pushvalue(L, updatecache(cs, idx));  /* get folding function */
    lua_insert(L, -2);  /* put it before accumulator */
    n = pushcapture(cs);  /* get next capture's values */
    lua_call(L, n + 1, 1);  /* call folding function */
  }
  cs->cap++;  /* skip close entry */
  return 1;  /* only accumulator left on the stack */
}