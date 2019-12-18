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
struct instance {int /*<<< orphan*/  pid_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nc_remove_pidfile(struct instance *nci)
{
    int status;

    status = unlink(nci->pid_filename);
    if (status < 0) {
        log_error("unlink of pid file '%s' failed, ignored: %s",
                  nci->pid_filename, strerror(errno));
    }
}