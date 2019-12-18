#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_5__ {int /*<<< orphan*/  realtime; int /*<<< orphan*/  monotonic; } ;
typedef  TYPE_1__ dual_timestamp ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  FORMAT_TIMESTAMP_MAX ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int boot_timestamps (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_from_monotonic (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_timespan (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_timestamp (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  log_full_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_boot_timestamps(void) {
        char s[MAX(FORMAT_TIMESPAN_MAX, FORMAT_TIMESTAMP_MAX)];
        dual_timestamp fw, l, k;
        int r;

        dual_timestamp_from_monotonic(&k, 0);

        r = boot_timestamps(NULL, &fw, &l);
        if (r < 0) {
                bool ok = r == -ENOENT || (getuid() != 0 && r == -EACCES) || r == -EOPNOTSUPP;

                log_full_errno(ok ? LOG_DEBUG : LOG_ERR, r, "Failed to read variables: %m");
                return ok ? 0 : r;
        }

        log_info("Firmware began %s before kernel.", format_timespan(s, sizeof(s), fw.monotonic, 0));
        log_info("Loader began %s before kernel.", format_timespan(s, sizeof(s), l.monotonic, 0));
        log_info("Firmware began %s.", format_timestamp(s, sizeof(s), fw.realtime));
        log_info("Loader began %s.", format_timestamp(s, sizeof(s), l.realtime));
        log_info("Kernel began %s.", format_timestamp(s, sizeof(s), k.realtime));
        return 1;
}