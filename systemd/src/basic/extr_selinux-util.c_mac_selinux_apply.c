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
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  log_enforcing_errno (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  mac_selinux_use () ; 
 scalar_t__ security_getenforce () ; 
 scalar_t__ setfilecon (char const*,char const*) ; 

int mac_selinux_apply(const char *path, const char *label) {

#if HAVE_SELINUX
        if (!mac_selinux_use())
                return 0;

        assert(path);
        assert(label);

        if (setfilecon(path, label) < 0) {
                log_enforcing_errno(errno, "Failed to set SELinux security context %s on path %s: %m", label, path);
                if (security_getenforce() > 0)
                        return -errno;
        }
#endif
        return 0;
}