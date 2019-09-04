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
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 int /*<<< orphan*/  atomic_load_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_max ; 
 int extent_in_dss_helper (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_dss ; 

bool
extent_in_dss(void *addr) {
	cassert(have_dss);

	return extent_in_dss_helper(addr, atomic_load_p(&dss_max,
	    ATOMIC_ACQUIRE));
}