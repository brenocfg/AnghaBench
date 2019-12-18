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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int arg_force ; 
 int arg_show_progress ; 
 int arg_skip ; 
 int /*<<< orphan*/  log_error (char*) ; 

__attribute__((used)) static void test_files(void) {

#if HAVE_SYSV_COMPAT
        if (access("/fastboot", F_OK) >= 0) {
                log_error("Please pass 'fsck.mode=skip' on the kernel command line rather than creating /fastboot on the root file system.");
                arg_skip = true;
        }

        if (access("/forcefsck", F_OK) >= 0) {
                log_error("Please pass 'fsck.mode=force' on the kernel command line rather than creating /forcefsck on the root file system.");
                arg_force = true;
        }
#endif

        arg_show_progress = access("/run/systemd/show-status", F_OK) >= 0;
}