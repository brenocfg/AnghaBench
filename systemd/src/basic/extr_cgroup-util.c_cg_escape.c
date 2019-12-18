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
typedef  scalar_t__ CGroupController ;

/* Variables and functions */
 scalar_t__ IN_SET (char const,int /*<<< orphan*/ ,char,char) ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*,char*) ; 
 scalar_t__ _CGROUP_CONTROLLER_MAX ; 
 char* cgroup_controller_to_string (scalar_t__) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 scalar_t__ startswith (char const*,char*) ; 
 char* strdup (char const*) ; 
 char* strjoin (char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

char *cg_escape(const char *p) {
        bool need_prefix = false;

        /* This implements very minimal escaping for names to be used
         * as file names in the cgroup tree: any name which might
         * conflict with a kernel name or is prefixed with '_' is
         * prefixed with a '_'. That way, when reading cgroup names it
         * is sufficient to remove a single prefixing underscore if
         * there is one. */

        /* The return value of this function (unlike cg_unescape())
         * needs free()! */

        if (IN_SET(p[0], 0, '_', '.') ||
            STR_IN_SET(p, "notify_on_release", "release_agent", "tasks") ||
            startswith(p, "cgroup."))
                need_prefix = true;
        else {
                const char *dot;

                dot = strrchr(p, '.');
                if (dot) {
                        CGroupController c;
                        size_t l = dot - p;

                        for (c = 0; c < _CGROUP_CONTROLLER_MAX; c++) {
                                const char *n;

                                n = cgroup_controller_to_string(c);

                                if (l != strlen(n))
                                        continue;

                                if (memcmp(p, n, l) != 0)
                                        continue;

                                need_prefix = true;
                                break;
                        }
                }
        }

        if (need_prefix)
                return strjoin("_", p);

        return strdup(p);
}