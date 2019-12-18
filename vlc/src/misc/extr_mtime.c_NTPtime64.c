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
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIME_UTC ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  timespec_get (struct timespec*,int /*<<< orphan*/ ) ; 

uint64_t NTPtime64(void)
{
    struct timespec ts;

    timespec_get(&ts, TIME_UTC);

    /* Convert nanoseconds to 32-bits fraction (232 picosecond units) */
    uint64_t t = (uint64_t)(ts.tv_nsec) << 32;
    t /= 1000000000;

    /* The offset to Unix epoch is 70 years (incl. 17 leap ones). There were
     * no leap seconds during that period since they had not been invented yet.
     */
    t |= ((UINT64_C(70) * 365 + 17) * 24 * 60 * 60 + ts.tv_sec) << 32;
    return t;
}