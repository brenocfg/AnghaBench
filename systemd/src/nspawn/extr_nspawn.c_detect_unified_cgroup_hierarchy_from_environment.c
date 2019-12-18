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
 int /*<<< orphan*/  CGROUP_UNIFIED_ALL ; 
 int /*<<< orphan*/  CGROUP_UNIFIED_NONE ; 
 int /*<<< orphan*/  arg_unified_cgroup_hierarchy ; 
 char* getenv (char const*) ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 int log_error_errno (int,char*,char const*) ; 
 int parse_boolean (char const*) ; 

__attribute__((used)) static int detect_unified_cgroup_hierarchy_from_environment(void) {
        const char *e, *var = "SYSTEMD_NSPAWN_UNIFIED_HIERARCHY";
        int r;

        /* Allow the user to control whether the unified hierarchy is used */

        e = getenv(var);
        if (!e) {
                /* $UNIFIED_CGROUP_HIERARCHY has been renamed to $SYSTEMD_NSPAWN_UNIFIED_HIERARCHY. */
                var = "UNIFIED_CGROUP_HIERARCHY";
                e = getenv(var);
        }

        if (!isempty(e)) {
                r = parse_boolean(e);
                if (r < 0)
                        return log_error_errno(r, "Failed to parse $%s: %m", var);
                if (r > 0)
                        arg_unified_cgroup_hierarchy = CGROUP_UNIFIED_ALL;
                else
                        arg_unified_cgroup_hierarchy = CGROUP_UNIFIED_NONE;
        }

        return 0;
}