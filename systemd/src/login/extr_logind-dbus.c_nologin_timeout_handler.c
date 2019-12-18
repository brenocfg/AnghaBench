#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_2__ {int unlink_nologin; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ create_shutdown_run_nologin_or_warn () ; 
 int /*<<< orphan*/  log_info (char*) ; 

__attribute__((used)) static int nologin_timeout_handler(
                        sd_event_source *s,
                        uint64_t usec,
                        void *userdata) {

        Manager *m = userdata;

        log_info("Creating /run/nologin, blocking further logins...");

        m->unlink_nologin =
                create_shutdown_run_nologin_or_warn() >= 0;

        return 0;
}