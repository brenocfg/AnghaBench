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
typedef  int /*<<< orphan*/  Capture ;

/* Variables and functions */
 scalar_t__ isclosecap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isfullcap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Capture *findopen (Capture *cap) {
  int n = 0;  /* number of closes waiting an open */
  for (;;) {
    cap--;
    if (isclosecap(cap)) n++;  /* one more open to skip */
    else if (!isfullcap(cap))
      if (n-- == 0) return cap;
  }
}