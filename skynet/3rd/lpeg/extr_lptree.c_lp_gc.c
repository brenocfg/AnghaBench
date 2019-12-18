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
typedef  int /*<<< orphan*/  Pattern ;

/* Variables and functions */
 int /*<<< orphan*/ * getpattern (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  realloccode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lp_gc (lua_State *L) {
  Pattern *p = getpattern(L, 1);
  realloccode(L, p, 0);  /* delete code block */
  return 0;
}