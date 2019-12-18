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
typedef  int uint64_t ;
struct statvfs {scalar_t__ f_bsize; scalar_t__ f_bfree; } ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  fb_need ;
typedef  int /*<<< orphan*/  fb_available ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_DISK_FULL ; 
 int FORMAT_BYTES_MAX ; 
 int RELOAD_DISK_SPACE_MIN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  format_bytes (char*,int,int) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ statvfs (char*,struct statvfs*) ; 

__attribute__((used)) static int verify_run_space(const char *message, sd_bus_error *error) {
        struct statvfs svfs;
        uint64_t available;

        if (statvfs("/run/systemd", &svfs) < 0)
                return sd_bus_error_set_errnof(error, errno, "Failed to statvfs(/run/systemd): %m");

        available = (uint64_t) svfs.f_bfree * (uint64_t) svfs.f_bsize;

        if (available < RELOAD_DISK_SPACE_MIN) {
                char fb_available[FORMAT_BYTES_MAX], fb_need[FORMAT_BYTES_MAX];
                return sd_bus_error_setf(error,
                                         BUS_ERROR_DISK_FULL,
                                         "%s, not enough space available on /run/systemd. "
                                         "Currently, %s are free, but a safety buffer of %s is enforced.",
                                         message,
                                         format_bytes(fb_available, sizeof(fb_available), available),
                                         format_bytes(fb_need, sizeof(fb_need), RELOAD_DISK_SPACE_MIN));
        }

        return 0;
}