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
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  ts_start ;
typedef  int /*<<< orphan*/  ts_span ;
typedef  int /*<<< orphan*/  ts_exit ;

/* Variables and functions */
 int EACCES ; 
 int ENODATA ; 
 int ENOENT ; 
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 int acpi_get_boot_usec (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  format_timespan (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  log_full_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_acpi_fpdt(void) {
        char ts_start[FORMAT_TIMESPAN_MAX], ts_exit[FORMAT_TIMESPAN_MAX], ts_span[FORMAT_TIMESPAN_MAX];
        usec_t loader_start, loader_exit;
        int r;

        r = acpi_get_boot_usec(&loader_start, &loader_exit);
        if (r < 0) {
                bool ok = r == -ENOENT || (getuid() != 0 && r == -EACCES) || r == -ENODATA;

                log_full_errno(ok ? LOG_DEBUG : LOG_ERR, r, "Failed to read ACPI FPDT: %m");
                return ok ? 0 : r;
        }

        log_info("ACPI FPDT: loader start=%s exit=%s duration=%s",
                 format_timespan(ts_start, sizeof(ts_start), loader_start, USEC_PER_MSEC),
                 format_timespan(ts_exit, sizeof(ts_exit), loader_exit, USEC_PER_MSEC),
                 format_timespan(ts_span, sizeof(ts_span), loader_exit - loader_start, USEC_PER_MSEC));
        return 1;
}