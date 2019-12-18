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
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/ ** sweeplist (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static GCObject **sweeptolive (lua_State *L, GCObject **p, int *n) {
  GCObject ** old = p;
  int i = 0;
  do {
    i++;
    p = sweeplist(L, p, 1);
  } while (p == old);
  if (n) *n += i;
  return p;
}