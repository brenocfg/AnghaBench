#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_3__ {int /*<<< orphan*/  timer_event; int /*<<< orphan*/  daemon; } ;
typedef  int /*<<< orphan*/  MHD_UNSIGNED_LONG_LONG ;
typedef  TYPE_1__ MHDDaemonWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int MHD_NO ; 
 int MHD_get_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MHD_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_EVENT_ON ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULLONG_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dispatch_http_event(sd_event_source *event,
                               int fd,
                               uint32_t revents,
                               void *userdata) {
        MHDDaemonWrapper *d = userdata;
        int r;
        MHD_UNSIGNED_LONG_LONG timeout = ULLONG_MAX;

        assert(d);

        r = MHD_run(d->daemon);
        if (r == MHD_NO)
                // FIXME: unregister daemon
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "MHD_run failed!");
        if (MHD_get_timeout(d->daemon, &timeout) == MHD_NO)
                timeout = ULLONG_MAX;

        r = sd_event_source_set_time(d->timer_event, timeout);
        if (r < 0) {
                log_warning_errno(r, "Unable to set event loop timeout: %m, this may result in indefinite blocking!");
                return 1;
        }

        r = sd_event_source_set_enabled(d->timer_event, SD_EVENT_ON);
        if (r < 0)
                log_warning_errno(r, "Unable to enable timer_event: %m, this may result in indefinite blocking!");

        return 1; /* work to do */
}