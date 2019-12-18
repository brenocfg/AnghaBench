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
typedef  int key_serial_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYCTL_JOIN_SESSION_KEYRING ; 
 scalar_t__ errno ; 
 int keyctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug_errno (scalar_t__,char*) ; 
 int log_error_errno (scalar_t__,char*) ; 

__attribute__((used)) static int setup_keyring(void) {
        key_serial_t keyring;

        /* Allocate a new session keyring for the container. This makes sure the keyring of the session systemd-nspawn
         * was invoked from doesn't leak into the container. Note that by default we block keyctl() and request_key()
         * anyway via seccomp so doing this operation isn't strictly necessary, but in case people explicitly whitelist
         * these system calls let's make sure we don't leak anything into the container. */

        keyring = keyctl(KEYCTL_JOIN_SESSION_KEYRING, 0, 0, 0, 0);
        if (keyring == -1) {
                if (errno == ENOSYS)
                        log_debug_errno(errno, "Kernel keyring not supported, ignoring.");
                else if (IN_SET(errno, EACCES, EPERM))
                        log_debug_errno(errno, "Kernel keyring access prohibited, ignoring.");
                else
                        return log_error_errno(errno, "Setting up kernel keyring failed: %m");
        }

        return 0;
}