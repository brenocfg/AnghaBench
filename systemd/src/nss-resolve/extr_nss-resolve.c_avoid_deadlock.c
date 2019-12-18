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
 int /*<<< orphan*/  getenv (char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ streq_ptr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool avoid_deadlock(void) {

        /* Check whether this lookup might have a chance of deadlocking because we are called from the service manager
         * code activating systemd-resolved.service. After all, we shouldn't synchronously do lookups to
         * systemd-resolved if we are required to finish before it can be started. This of course won't detect all
         * possible dead locks of this kind, but it should work for the most obvious cases. */

        if (geteuid() != 0) /* Ignore the env vars unless we are privileged. */
                return false;

        return streq_ptr(getenv("SYSTEMD_ACTIVATION_UNIT"), "systemd-resolved.service") &&
               streq_ptr(getenv("SYSTEMD_ACTIVATION_SCOPE"), "system");
}