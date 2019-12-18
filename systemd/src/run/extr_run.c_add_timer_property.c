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
 int /*<<< orphan*/  arg_timer_property ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int log_oom () ; 
 char* strjoin (char const*,char*,char const*) ; 
 scalar_t__ strv_consume (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int add_timer_property(const char *name, const char *val) {
        char *p;

        assert(name);
        assert(val);

        p = strjoin(name, "=", val);
        if (!p)
                return log_oom();

        if (strv_consume(&arg_timer_property, p) < 0)
                return log_oom();

        return 0;
}