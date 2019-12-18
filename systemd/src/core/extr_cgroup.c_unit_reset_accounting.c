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
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int unit_reset_cpu_accounting (int /*<<< orphan*/ *) ; 
 int unit_reset_io_accounting (int /*<<< orphan*/ *) ; 
 int unit_reset_ip_accounting (int /*<<< orphan*/ *) ; 

int unit_reset_accounting(Unit *u) {
        int r, q, v;

        assert(u);

        r = unit_reset_cpu_accounting(u);
        q = unit_reset_io_accounting(u);
        v = unit_reset_ip_accounting(u);

        return r < 0 ? r : q < 0 ? q : v;
}