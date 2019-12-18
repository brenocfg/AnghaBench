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

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 unsigned long long MEASURE_ITERATIONS ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getpid_cached () ; 
 int /*<<< orphan*/  log_info (char*,double) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_getpid_measure(void) {
        unsigned long long i;
        usec_t t, q;

        t = now(CLOCK_MONOTONIC);
        for (i = 0; i < MEASURE_ITERATIONS; i++)
                (void) getpid();
        q = now(CLOCK_MONOTONIC) - t;

        log_info(" glibc getpid(): %lf µs each\n", (double) q / MEASURE_ITERATIONS);

        t = now(CLOCK_MONOTONIC);
        for (i = 0; i < MEASURE_ITERATIONS; i++)
                (void) getpid_cached();
        q = now(CLOCK_MONOTONIC) - t;

        log_info("getpid_cached(): %lf µs each\n", (double) q / MEASURE_ITERATIONS);
}