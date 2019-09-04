#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * cap; } ;
typedef  int /*<<< orphan*/  Capture ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/ * findback (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushluaval (TYPE_1__*) ; 
 int pushnestedvalues (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int backrefcap (CapState *cs) {
  int n;
  Capture *curr = cs->cap;
  pushluaval(cs);  /* reference name */
  cs->cap = findback(cs, curr);  /* find corresponding group */
  n = pushnestedvalues(cs, 0);  /* push group's values */
  cs->cap = curr + 1;
  return n;
}