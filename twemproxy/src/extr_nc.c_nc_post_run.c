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
struct instance {scalar_t__ pidfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_deinit () ; 
 int /*<<< orphan*/  nc_print_done () ; 
 int /*<<< orphan*/  nc_remove_pidfile (struct instance*) ; 
 int /*<<< orphan*/  signal_deinit () ; 

__attribute__((used)) static void
nc_post_run(struct instance *nci)
{
    if (nci->pidfile) {
        nc_remove_pidfile(nci);
    }

    signal_deinit();

    nc_print_done();

    log_deinit();
}