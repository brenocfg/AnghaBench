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
struct stat {int /*<<< orphan*/  st_mtim; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int apply_timestamp (char*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_setup_service () ; 
 int mac_selinux_init () ; 
 scalar_t__ stat (char*,struct stat*) ; 

int main(int argc, char *argv[]) {
        struct stat st;
        int r, q = 0;

        log_setup_service();

        if (stat("/usr", &st) < 0) {
                log_error_errno(errno, "Failed to stat /usr: %m");
                return EXIT_FAILURE;
        }

        r = mac_selinux_init();
        if (r < 0) {
                log_error_errno(r, "SELinux setup failed: %m");
                return EXIT_FAILURE;
        }

        r = apply_timestamp("/etc/.updated", &st.st_mtim);
        q = apply_timestamp("/var/.updated", &st.st_mtim);

        return r < 0 || q < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}