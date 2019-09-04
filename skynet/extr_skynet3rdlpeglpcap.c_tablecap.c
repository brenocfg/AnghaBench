#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ idx; } ;
struct TYPE_8__ {TYPE_6__* cap; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 scalar_t__ Cgroup ; 
 scalar_t__ captype (TYPE_6__*) ; 
 int /*<<< orphan*/  isclosecap (TYPE_6__*) ; 
 scalar_t__ isfullcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int pushcapture (TYPE_1__*) ; 
 int /*<<< orphan*/  pushluaval (TYPE_1__*) ; 
 int /*<<< orphan*/  pushonenestedvalue (TYPE_1__*) ; 

__attribute__((used)) static int tablecap (CapState *cs) {
  lua_State *L = cs->L;
  int n = 0;
  lua_newtable(L);
  if (isfullcap(cs->cap++))
    return 1;  /* table is empty */
  while (!isclosecap(cs->cap)) {
    if (captype(cs->cap) == Cgroup && cs->cap->idx != 0) {  /* named group? */
      pushluaval(cs);  /* push group name */
      pushonenestedvalue(cs);
      lua_settable(L, -3);
    }
    else {  /* not a named group */
      int i;
      int k = pushcapture(cs);
      for (i = k; i > 0; i--)  /* store all values into table */
        lua_rawseti(L, -(i + 1), n + i);
      n += k;
    }
  }
  cs->cap++;  /* skip close entry */
  return 1;  /* number of values pushed (only the table) */
}