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
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_zu_eq (int /*<<< orphan*/ ,size_t,char*,char const*,int) ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 void* mallocx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_bt_count () ; 

__attribute__((used)) static void
prof_sampling_probe_impl(bool expect_sample, const char *func, int line) {
	void *p;
	size_t expected_backtraces = expect_sample ? 1 : 0;

	assert_zu_eq(prof_bt_count(), 0, "%s():%d: Expected 0 backtraces", func,
	    line);
	p = mallocx(1, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() failure");
	assert_zu_eq(prof_bt_count(), expected_backtraces,
	    "%s():%d: Unexpected backtrace count", func, line);
	dallocx(p, 0);
}