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
typedef  int /*<<< orphan*/  thread_name_old ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  assert_str_eq (char const*,char const*,char*,char const*,int) ; 
 int /*<<< orphan*/  mallctl (char*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mallctl_thread_name_get_impl(const char *thread_name_expected, const char *func,
    int line) {
	const char *thread_name_old;
	size_t sz;

	sz = sizeof(thread_name_old);
	assert_d_eq(mallctl("thread.prof.name", (void *)&thread_name_old, &sz,
	    NULL, 0), 0,
	    "%s():%d: Unexpected mallctl failure reading thread.prof.name",
	    func, line);
	assert_str_eq(thread_name_old, thread_name_expected,
	    "%s():%d: Unexpected thread.prof.name value", func, line);
}