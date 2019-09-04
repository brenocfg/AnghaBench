#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cap; } ;
typedef  int /*<<< orphan*/  Capture ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 scalar_t__ isclosecap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isfullcap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nextcap (CapState *cs) {
  Capture *cap = cs->cap;
  if (!isfullcap(cap)) {  /* not a single capture? */
    int n = 0;  /* number of opens waiting a close */
    for (;;) {  /* look for corresponding close */
      cap++;
      if (isclosecap(cap)) {
        if (n-- == 0) break;
      }
      else if (!isfullcap(cap)) n++;
    }
  }
  cs->cap = cap + 1;  /* + 1 to skip last close (or entire single capture) */
}