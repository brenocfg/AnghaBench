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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int log_error_errno (int,char*,char const*,...) ; 
 int mac_smack_copy (char const*,char const*) ; 
 char* strjoina (char*,char const*) ; 
 int symlink_idempotent (char const*,char const*,int) ; 

__attribute__((used)) static int symlink_controller(const char *target, const char *alias) {
        const char *a;
        int r;

        assert(target);
        assert(alias);

        a = strjoina("/sys/fs/cgroup/", alias);

        r = symlink_idempotent(target, a, false);
        if (r < 0)
                return log_error_errno(r, "Failed to create symlink %s: %m", a);

#ifdef SMACK_RUN_LABEL
        const char *p;

        p = strjoina("/sys/fs/cgroup/", target);

        r = mac_smack_copy(a, p);
        if (r < 0 && r != -EOPNOTSUPP)
                return log_error_errno(r, "Failed to copy smack label from %s to %s: %m", p, a);
#endif

        return 0;
}