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
struct instance {scalar_t__ pid_filename; int /*<<< orphan*/  pid; int /*<<< orphan*/  log_filename; int /*<<< orphan*/  log_level; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ log_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nc_create_pidfile (struct instance*) ; 
 scalar_t__ nc_daemonize (int) ; 
 int /*<<< orphan*/  nc_print_run (struct instance*) ; 
 scalar_t__ signal_init () ; 

__attribute__((used)) static rstatus_t
nc_pre_run(struct instance *nci)
{
    rstatus_t status;

    status = log_init(nci->log_level, nci->log_filename);
    if (status != NC_OK) {
        return status;
    }

    if (daemonize) {
        status = nc_daemonize(1);
        if (status != NC_OK) {
            return status;
        }
    }

    nci->pid = getpid();

    status = signal_init();
    if (status != NC_OK) {
        return status;
    }

    if (nci->pid_filename) {
        status = nc_create_pidfile(nci);
        if (status != NC_OK) {
            return status;
        }
    }

    nc_print_run(nci);

    return NC_OK;
}