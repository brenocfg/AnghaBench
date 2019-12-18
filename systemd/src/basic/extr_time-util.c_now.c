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
typedef  int /*<<< orphan*/  usec_t ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  map_clock_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec_load (struct timespec*) ; 

usec_t now(clockid_t clock_id) {
        struct timespec ts;

        assert_se(clock_gettime(map_clock_id(clock_id), &ts) == 0);

        return timespec_load(&ts);
}