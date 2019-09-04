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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int64_t
nc_usec_now(void)
{
    struct timeval now;
    int64_t usec;
    int status;

    status = gettimeofday(&now, NULL);
    if (status < 0) {
        log_error("gettimeofday failed: %s", strerror(errno));
        return -1;
    }

    usec = (int64_t)now.tv_sec * 1000000LL + (int64_t)now.tv_usec;

    return usec;
}