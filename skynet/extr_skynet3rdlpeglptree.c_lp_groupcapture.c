#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  Cgroup ; 
 int capture_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lp_groupcapture (lua_State *L) {
  if (lua_isnoneornil(L, 2))
    return capture_aux(L, Cgroup, 0);
  else
    return capture_aux(L, Cgroup, 2);
}