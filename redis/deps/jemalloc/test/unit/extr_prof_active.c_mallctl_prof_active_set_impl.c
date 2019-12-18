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
 int /*<<< orphan*/  mallctl_bool_set (char*,int,int,char const*,int) ; 

__attribute__((used)) static void
mallctl_prof_active_set_impl(bool prof_active_old_expected,
    bool prof_active_new, const char *func, int line) {
	mallctl_bool_set("prof.active", prof_active_old_expected,
	    prof_active_new, func, line);
}