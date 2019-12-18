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
 int log_error_errno (int,char*) ; 
 int write_string_file_atomic_label (char*,char*) ; 

int create_shutdown_run_nologin_or_warn(void) {
        int r;

        /* This is used twice: once in systemd-user-sessions.service, in order to block logins when we actually go
         * down, and once in systemd-logind.service when shutdowns are scheduled, and logins are to be turned off a bit
         * in advance. We use the same wording of the message in both cases. */

        r = write_string_file_atomic_label("/run/nologin",
                                           "System is going down. Unprivileged users are not permitted to log in anymore. "
                                           "For technical details, see pam_nologin(8).");
        if (r < 0)
                return log_error_errno(r, "Failed to create /run/nologin: %m");

        return 0;
}