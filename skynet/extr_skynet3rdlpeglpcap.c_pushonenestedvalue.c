#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int pushnestedvalues (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pushonenestedvalue (CapState *cs) {
  int n = pushnestedvalues(cs, 0);
  if (n > 1)
    lua_pop(cs->L, n - 1);  /* pop extra values */
}