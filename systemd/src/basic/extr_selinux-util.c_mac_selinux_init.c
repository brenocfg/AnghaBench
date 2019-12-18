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
typedef  int /*<<< orphan*/  timespan ;
struct mallinfo {scalar_t__ uordblks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  SELABEL_CTX_FILE ; 
 int errno ; 
 int /*<<< orphan*/  format_timespan (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ label_hnd ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_enforcing_errno (int,char*) ; 
 int /*<<< orphan*/  mac_selinux_use () ; 
 struct mallinfo mallinfo () ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int security_getenforce () ; 
 scalar_t__ selabel_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mac_selinux_init(void) {
        int r = 0;

#if HAVE_SELINUX
        usec_t before_timestamp, after_timestamp;
        struct mallinfo before_mallinfo, after_mallinfo;

        if (label_hnd)
                return 0;

        if (!mac_selinux_use())
                return 0;

        before_mallinfo = mallinfo();
        before_timestamp = now(CLOCK_MONOTONIC);

        label_hnd = selabel_open(SELABEL_CTX_FILE, NULL, 0);
        if (!label_hnd) {
                log_enforcing_errno(errno, "Failed to initialize SELinux context: %m");
                r = security_getenforce() == 1 ? -errno : 0;
        } else  {
                char timespan[FORMAT_TIMESPAN_MAX];
                int l;

                after_timestamp = now(CLOCK_MONOTONIC);
                after_mallinfo = mallinfo();

                l = after_mallinfo.uordblks > before_mallinfo.uordblks ? after_mallinfo.uordblks - before_mallinfo.uordblks : 0;

                log_debug("Successfully loaded SELinux database in %s, size on heap is %iK.",
                          format_timespan(timespan, sizeof(timespan), after_timestamp - before_timestamp, 0),
                          (l+1023)/1024);
        }
#endif

        return r;
}