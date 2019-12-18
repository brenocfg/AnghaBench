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

/* Variables and functions */
 scalar_t__ arc_initialized ; 
 int /*<<< orphan*/  arc_reap_zthr ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  zthr_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdr_recl(void *unused)
{
	dprintf("hdr_recl called\n");
	/*
	 * umem calls the reclaim func when we destroy the buf cache,
	 * which is after we do arc_fini().
	 */
	if (arc_initialized)
		zthr_wakeup(arc_reap_zthr);
}