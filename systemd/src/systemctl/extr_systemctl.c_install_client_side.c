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
 scalar_t__ UNIT_FILE_GLOBAL ; 
 int /*<<< orphan*/  arg_root ; 
 scalar_t__ arg_scope ; 
 scalar_t__ getenv_bool (char*) ; 
 int /*<<< orphan*/  isempty (int /*<<< orphan*/ ) ; 
 scalar_t__ running_in_chroot_or_offline () ; 
 scalar_t__ sd_booted () ; 

__attribute__((used)) static bool install_client_side(void) {
        /* Decides when to execute enable/disable/... operations
         * client-side rather than server-side. */

        if (running_in_chroot_or_offline())
                return true;

        if (sd_booted() <= 0)
                return true;

        if (!isempty(arg_root))
                return true;

        if (arg_scope == UNIT_FILE_GLOBAL)
                return true;

        /* Unsupported environment variable, mostly for debugging purposes */
        if (getenv_bool("SYSTEMCTL_INSTALL_CLIENT_SIDE") > 0)
                return true;

        return false;
}