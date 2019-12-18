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
 int /*<<< orphan*/  log_enforcing_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  mac_selinux_use () ; 
 int security_getenforce () ; 
 scalar_t__ setsockcreatecon (char const*) ; 

int mac_selinux_create_socket_prepare(const char *label) {

#if HAVE_SELINUX
        if (!mac_selinux_use())
                return 0;

        assert(label);

        if (setsockcreatecon(label) < 0) {
                log_enforcing_errno(errno, "Failed to set SELinux security context %s for sockets: %m", label);

                if (security_getenforce() == 1)
                        return -errno;
        }
#endif

        return 0;
}