#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_13__ {int /*<<< orphan*/  ocap; int /*<<< orphan*/ * L; } ;
struct TYPE_12__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_1__ Capture ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 scalar_t__ Cgroup ; 
 scalar_t__ captype (TYPE_1__*) ; 
 TYPE_1__* findopen (TYPE_1__*) ; 
 int /*<<< orphan*/  getfromktable (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isclosecap (TYPE_1__*) ; 
 int /*<<< orphan*/  isfullcap (TYPE_1__*) ; 
 scalar_t__ lp_equal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Capture *findback (CapState *cs, Capture *cap) {
  lua_State *L = cs->L;
  while (cap-- > cs->ocap) {  /* repeat until end of list */
    if (isclosecap(cap))
      cap = findopen(cap);  /* skip nested captures */
    else if (!isfullcap(cap))
      continue; /* opening an enclosing capture: skip and get previous */
    if (captype(cap) == Cgroup) {
      getfromktable(cs, cap->idx);  /* get group name */
      if (lp_equal(L, -2, -1)) {  /* right group? */
        lua_pop(L, 2);  /* remove reference name and group name */
        return cap;
      }
      else lua_pop(L, 1);  /* remove group name */
    }
  }
  luaL_error(L, "back reference '%s' not found", lua_tostring(L, -1));
  return NULL;  /* to avoid warnings */
}